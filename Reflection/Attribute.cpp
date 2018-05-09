#include "Attribute.hpp"

namespace YTE
{
  YTEDefineType(Attribute)
  {
    RegisterType<Attribute>();
    TypeBuilder<Attribute> builder;
  }

  YTEDefineType(Serializable)
  {
    RegisterType<Serializable>();
    TypeBuilder<Serializable> builder;
  }

  YTEDefineType(RunInEditor)
  {
    RegisterType<RunInEditor>();
    TypeBuilder<RunInEditor> builder;
  }

  YTEDefineType(EditableColor)
  {
    RegisterType<EditableColor>();
    TypeBuilder<EditableColor> builder;
  }

  void PropertyChecked(const char *, DocumentedObject *)
  {
  }

  Serializable::Serializable(DocumentedObject *aObject)
  {
    PropertyChecked("Serializable", aObject);
  }

  YTEDefineType(EditorProperty)
  {
    RegisterType<EditorProperty>();
    TypeBuilder<EditorProperty> builder;
  }

  YTEDefineType(DropDownStrings)
  {
    RegisterType<DropDownStrings>();
    TypeBuilder<DropDownStrings> builder;
  }

  EditorProperty::EditorProperty(DocumentedObject *aObject, bool aVisible)
    : mVisible(aVisible)
  {
    PropertyChecked("EditorProperty", aObject);
  }

  DropDownStrings::DropDownStrings(DocumentedObject *aObject, StrGettor aStrGettor)
    : mStringGettor(aStrGettor)
  {
    auto prop = dynamic_cast<Property*>(aObject);
    YTEUnusedArgument(prop);
  }

  StrGettor DropDownStrings::GetStringGettor()
  {
    return mStringGettor;
  }
}

