#pragma once

#include <iostream>

#include "Reflection/StandardLibrary/Any.hpp"

class Function : public DocumentedObject
{
public:
  DeclareType(Function)
  Function(Function&) = delete;

  using CallingFunction = Any(*)(std::vector<Any>& arguments);

  struct Parameter
  {
    Parameter(Type *aType, const char *aName)
      : mType(aType),
      mName(aName)
    {

    }

    Type *mType;
    std::string mName;
  };

  Function(const char *aName, Type *aReturnType, Type *aOwningType, bool aStaticOrFree)
    : mName(aName),
      mReturnType(aReturnType),
      mCaller(nullptr),
      mOwningType(aOwningType),
      mStaticOrFree(aStaticOrFree)
  {
    if ((aOwningType == nullptr) && (mStaticOrFree == false))
    {
      runtime_assert(false,
        "A function without an owning type is, by definition, static.");
    }
  }

  // Will return default constructed Any if the arguments fail.
  Any Invoke(std::vector<Any> &aArguments) const
  {
    if (mParameters.size() != aArguments.size())
    {
      std::cout << "Different argument amounts." << std::endl;
      return Any();
    }

    for (size_t i = 0; i < mParameters.size(); ++i)
    {
      if (mParameters[i].mType != aArguments[i].mType && 
          mParameters[i].mType->GetReferenceTo() != aArguments[i].mType)
      {
        std::cout << "Different argument types." << std::endl;
        return Any();
      }
    }

    return mCaller(aArguments);
  }

  // Will return default constructed Any if the arguments fail.
  template <typename ...Arguments>
  Any Invoke(Arguments...aArguments) const
  {
    auto args = Any::FromVariadic<Arguments...>(aArguments...);

    return Invoke(args);
  }

  void AddParameter(Type *aType, const char *aName = "")
  {
    mParameters.emplace_back(aType, aName);
  }

  void SetCaller(CallingFunction aCaller)
  {
    mCaller = aCaller;
  }

  const std::string& GetName() const
  {
    return mName;
  }

  const Type* GetOwningType() const
  {
    return mOwningType;
  }

  Type* GetReturnType() const
  {
    return mReturnType;
  }

private:
  std::string mName;
  std::vector<Parameter> mParameters;
  Type *mReturnType;
  CallingFunction mCaller;
  Type *mOwningType;
  bool mStaticOrFree;
};

template <typename T>
inline void AddParameter(Function *aFunction)
{
  aFunction->AddParameter(TypeId<T>());
}

template <typename... Rest> struct ParseArguments;

template <>
struct ParseArguments<>
{
  inline static void Parse(Function *aFunction)
  {
  }
};

template <typename First, typename... Rest>
struct ParseArguments<First, Rest...>
{
  inline static void Parse(Function *aFunction)
  {
    AddParameter<First>(aFunction);
    ParseArguments<Rest...>::Parse(aFunction);
  }
};

template <typename Return, typename Enable = void>
struct Binding {};


template <typename Return, typename... Arguments>
struct Binding<Return(*)(Arguments...), typename std::enable_if<std::is_void<Return>::value == false>::type >
{
  using FunctionSignature = Return(*)(Arguments...);
  using CallingType = Any(*)(std::vector<Any>&);

  template <FunctionSignature BoundFunc>
  static Any Caller(std::vector<Any>& arguments)
  {
    size_t i = 0;
    auto capture = BoundFunc(arguments.at(i++).As<Arguments>()...);
    Any toReturn{ &capture, TypeId<Return>() };
    return toReturn;
  }

  template <FunctionSignature BoundFunc>
  static std::unique_ptr<Function> BindFunction(const char *name)
  {
    auto function = std::make_unique<Function>(name, TypeId<Return>(), nullptr, true);
    ParseArguments<Arguments...>::Parse(function.get());

    function->SetCaller(Caller<BoundFunc>);

    return std::move(function);
  }
};

template <typename Return, typename... Arguments>
struct Binding<Return(*)(Arguments...), typename std::enable_if<std::is_void<Return>::value>::type >
{
  using FunctionSignature = Return(*)(Arguments...);
  using CallingType = Any(*)(std::vector<Any>&);

  template <FunctionSignature BoundFunc>
  static Any Caller(std::vector<Any>& arguments)
  {
    size_t i = 0;
    BoundFunc(arguments.at(i++).As<Arguments>()...);
    return Any();
  }

  static std::unique_ptr<Function> BindPassedFunction(const char *name, CallingType aCaller)
  {
    auto function = std::make_unique<Function>(name, TypeId<Return>(), nullptr, true);
    ParseArguments<Arguments...>::Parse(function.get());

    function->SetCaller(aCaller);

    return std::move(function);
  }

  template <FunctionSignature BoundFunc>
  static std::unique_ptr<Function> BindFunction(const char *name)
  {
    auto function = std::make_unique<Function>(name, TypeId<Return>(), nullptr, true);
    ParseArguments<Arguments...>::Parse(function.get());

    function->SetCaller(Caller<BoundFunc>);

    return std::move(function);
  }
};

template <typename Return, typename ObjectType, typename... Arguments>
struct Binding<Return(ObjectType::*)(Arguments...), typename std::enable_if<std::is_void<Return>::value == false>::type>
{
  using FunctionSignature = Return(ObjectType::*)(Arguments...);
  using CallingType = Any(*)(std::vector<Any>&);

  template <FunctionSignature BoundFunc>
  static Any Caller(std::vector<Any>& arguments)
  {
    auto self = arguments.at(0).As<ObjectType*>();

    size_t i = 1;
    auto capture = (self->*BoundFunc)(arguments.at(i++).As<Arguments>()...);
    Any toReturn{ &capture, TypeId<Return>() };
    return toReturn;
  }




  template <FunctionSignature BoundFunc>
  static std::unique_ptr<Function> BindFunction(const char *name)
  {
    auto function = std::make_unique<Function>(name, TypeId<Return>(), TypeId<ObjectType>(), false);
    function->AddParameter(TypeId<ObjectType*>());
    ParseArguments<Arguments...>::Parse(function.get());

    function->SetCaller(Caller<BoundFunc>);

    return std::move(function);
  }



  static std::unique_ptr<Function> BindPassedFunction(const char *name, CallingType aCaller)
  {
    auto function = std::make_unique<Function>(name, TypeId<Return>(), TypeId<ObjectType>(), false);
    function->AddParameter(TypeId<ObjectType*>());
    ParseArguments<Arguments...>::Parse(function.get());
  
    function->SetCaller(aCaller);
  
    return std::move(function);
  }
};


template <typename Return, typename ObjectType, typename... Arguments>
struct Binding<Return(ObjectType::*)(Arguments...), typename std::enable_if<std::is_void<Return>::value>::type>
{
  using FunctionSignature = Return(ObjectType::*)(Arguments...);
  using CallingType = Any(*)(std::vector<Any>&);

  template <FunctionSignature BoundFunc>
  static Any Caller(std::vector<Any>& arguments)
  {
    auto self = arguments.at(0).As<ObjectType*>();

    size_t i = 1;
    (self->*BoundFunc)(arguments.at(i++).As<Arguments>()...);

    return Any();
  }


  static std::unique_ptr<Function> BindPassedFunction(const char *name, CallingType aCaller)
  {
    auto function = std::make_unique<Function>(name, TypeId<Return>(), TypeId<ObjectType>(), false);
    function->AddParameter(TypeId<ObjectType*>());
    ParseArguments<Arguments...>::Parse(function.get());

    function->SetCaller(aCaller);

    return std::move(function);
  }

  template <FunctionSignature BoundFunc>
  static std::unique_ptr<Function> BindFunction(const char *name)
  {
    auto function = std::make_unique<Function>(name, TypeId<Return>(), TypeId<ObjectType>(), false);
    function->AddParameter(TypeId<ObjectType*>());
    ParseArguments<Arguments...>::Parse(function.get());

    function->SetCaller(Caller<BoundFunc>);

    return std::move(function);
  }
};



template <>
struct Binding<nullptr_t>
{
  template <nullptr_t BoundFunc>
  static std::unique_ptr<Function> BindFunction(const char *name)
  {
    return std::unique_ptr<Function>();
  }
};

template <typename FunctionSignature, FunctionSignature BoundFunc>
static std::unique_ptr<Function> BindFunction(const char *name)
{
  return Binding<FunctionSignature>:: template BindFunction<BoundFunc>(name);
}
