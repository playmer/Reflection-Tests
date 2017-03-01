#pragma once

#include "Property.hpp"

class Field : public Property
{
public:
  Field(const char *aName,
        std::unique_ptr<Function> aGetter, 
        std::unique_ptr<Function> aSetter)
   : Property(aName, std::move(aGetter), std::move(aSetter))
  {
    runtime_assert((nullptr != mGetter) && (nullptr != mSetter), 
                   "Both the getter and setter must be set.");
  }

  template<typename FieldPointerType, FieldPointerType aFieldPointer>
  static Any Getter(std::vector<Any>& aArguments)
  {
    auto self = aArguments.at(0).As<typename DecomposeFieldPointer<FieldPointerType>::ObjectType*>();
    return Any(self->*aFieldPointer);
  }

  template<typename FieldPointerType, FieldPointerType aFieldPointer>
  static Any Setter(std::vector<Any>& aArguments)
  {
    auto self = aArguments.at(0).As<typename DecomposeFieldPointer<FieldPointerType>::ObjectType*>();
    self->*aFieldPointer = aArguments.at(1).As<typename DecomposeFieldPointer<FieldPointerType>::FieldType>();
    return Any();
  }

private:
};




template<typename FieldPointerType, FieldPointerType aFieldPointer>
static std::unique_ptr<Field> BindField(const char *aName)
{
  using ObjectType = typename DecomposeFieldPointer<FieldPointerType>::ObjectType;
  using FieldType = typename DecomposeFieldPointer<FieldPointerType>::FieldType;
  auto getter = Binding<FieldType (ObjectType::*)()>::BindFunction("Getter", Field::Getter<FieldPointerType, aFieldPointer>);
  auto setter = Binding<void(ObjectType::*)(FieldType)>::BindFunction("Setter", Field::Setter<FieldPointerType, aFieldPointer>);
  return std::make_unique <Field> (aName, std::move(getter), std::move(setter));
}

