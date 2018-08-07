#include <iostream>
#include "Meta.hpp"

namespace YTE
{
  class XboxController
  {
  public:
    YTEDeclareType(XboxController);
  };

  YTEDefineType(XboxController)
  {
    RegisterType<XboxController>();
  }

  enum class ControllerId : uint32_t
  {
    Xbox_P1,
    Xbox_P2,
    Xbox_P3,
    Xbox_P4,
    Xbox_Controllers_Number,
    Unknown
  };


  static XboxController* STATIC_GetXboxController(ControllerId aId)
  {
    return nullptr;
  }

  class GamepadSystem
  {
  public:
    YTEDeclareType(GamepadSystem);
    XboxController* GetXboxControllerConst(ControllerId aId) const
    {
      return nullptr;
    }

    XboxController* GetXboxController(ControllerId aId)
    {
      return nullptr;
    }

    void Set(ControllerId) {};
    ControllerId Get() { return ControllerId::Xbox_P1; };
  };

  YTEDefineType(GamepadSystem)
  {
    RegisterType<GamepadSystem>();
    TypeBuilder<GamepadSystem> builder;
    builder.Property<&GamepadSystem::Get, &GamepadSystem::Set>("Id");
  }
}

YTEDeclareExternalType(YTE::ControllerId);

YTEDefineExternalType(YTE::ControllerId)
{
  RegisterType<YTE::ControllerId>();

  TypeBuilder<YTE::ControllerId> builder;

  builder.Enum<YTE::ControllerId::Xbox_P1>("Xbox_P1");
}


int main()
{
}







































//#include <string>
//
//
//
//
//template <typename Return>
//struct CountFunctionArguments
//{
//
//};
//
//template <typename Return, typename ...Arguments>
//struct CountFunctionArguments<Return(Arguments...)>
//{
//  constexpr static size_t Size()
//  {
//    return sizeof...(Arguments);
//  }
//};
//
//template <typename Return, typename ...Arguments>
//struct CountFunctionArguments<Return(Arguments...) noexcept>
//  : public CountFunctionArguments<Return(Arguments...)>
//{
//};
//
//template <typename Return, typename ...Arguments>
//struct CountFunctionArguments<Return(*)(Arguments...)>
//  : public CountFunctionArguments<Return(Arguments...)>
//{
//};
//
//template <typename Return, typename ...Arguments>
//struct CountFunctionArguments<Return(*)(Arguments...) noexcept>
//  : public CountFunctionArguments<Return(Arguments...)>
//{
//};
//
//template <typename Return, typename Object, typename ...Arguments>
//struct CountFunctionArguments<Return(Object::*)(Arguments...)>
//  : public CountFunctionArguments<Return(Arguments...)>
//{
//};
//
//template <typename Return, typename Object, typename ...Arguments>
//struct CountFunctionArguments<Return(Object::*)(Arguments...) const>
//  : public CountFunctionArguments<Return(Arguments...)>
//{
//};
//
//
//
//namespace Detail
//{
//  // This is needed to workaround a bug in MSVC relating to using
//  // decltype on auto template parameters. It will sometimes not
//  // deduce the correct type and thus fail some template matching
//  // attempts that should succeed.
//  // Bug reported here: https://developercommunity.visualstudio.com/content/problem/248892/failed-template-matching-with-auto-parameter.html
//  // Can be removed when bug is fixed.
//  template<typename T> T GetTypeMSVCWorkaround(T);
//}
//
//
//template <typename tType>
//class TypeBuilder
//{
//  public:
//  template <typename tFunctionSignature>
//  class FunctionBuilder
//  {
//    public:
//    FunctionBuilder()
//    {
//
//    }
//
//    template <typename... tArguments>
//    void SetParameterNames(tArguments&& ...aNames)
//    {
//      constexpr size_t passedNames = sizeof...(aNames);
//      constexpr size_t funcNames = CountFunctionArguments<tFunctionSignature>::Size();
//      static_assert(0 != funcNames, "You needn't set the parameter names for this function, as there are no parameters.");
//
//      static_assert(passedNames == funcNames,
//                    "If passing names of function parameters you must pass either exactly as many names as there are arguments, or 0.");
//    }
//  };
//
//
//  template <auto tBoundFunction>
//  auto Function(char const* aName)
//  {
//    using FunctionSignature = decltype(Detail::GetTypeMSVCWorkaround(tBoundFunction));
//
//    return FunctionBuilder<FunctionSignature>{ };
//  }
//};
//
//
//struct Type
//{
//  public:
//  static Type* GetGlobalType(const std::string &aName);
//
//  static void InitializeTypeInfo()
//  {
//    TypeBuilder<Type> builder;
//    builder.Function<&Type::GetGlobalType>("GetGlobalType")
//      .SetParameterNames("aName");
//  }
//};





