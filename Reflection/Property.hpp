#pragma once

#include "Types.hpp"
#include "Function.hpp"

// TODO: Have some requirements on the types of setters and getters.
class Property : public DocumentedObject
{
public:
  DeclareType(Property)

  Property(Property&) = delete;

  Property(const char *aName, 
           std::unique_ptr<Function> aGetter, 
           std::unique_ptr<Function> aSetter)
   : mName(aName),
     mGetter(std::move(aGetter)),
     mSetter(std::move(aSetter))
  {
    runtime_assert((nullptr != mGetter) || (nullptr != mSetter), 
                   "At least one of the getter and setter must be set.");
  }

  const std::string& GetName() { return mName; }
  Function* GetGetter() { return mGetter.get(); }
  Function* GetSetter() { return mSetter.get(); }
protected:
  std::string mName;
  std::unique_ptr<Function> mGetter;
  std::unique_ptr<Function> mSetter;
};



template <typename GetterFunctionSignature, GetterFunctionSignature GetterFunction, 
          typename SetterFunctionSignature, SetterFunctionSignature SetterFunction>
static std::unique_ptr<Property> BindProperty(const char *aName)
{
  auto getter = Binding<GetterFunctionSignature>::BindFunction<GetterFunction>("Getter");
  auto setter = Binding<SetterFunctionSignature>::BindFunction<SetterFunction>("Setter");
  return std::make_unique<Property>(aName, std::move(getter), std::move(setter));
}