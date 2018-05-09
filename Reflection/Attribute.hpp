#pragma once
#include "Meta.hpp"

namespace YTE
{
  class Component;
  class Object;

  class Attribute : public Base
  {
  public:
    YTEDeclareType(Attribute)
  };

  class Serializable : public Attribute
  {
  public:
    YTEDeclareType(Serializable);
    Serializable(DocumentedObject *aObject);
  };

  class RunInEditor : public Attribute
  {
  public:
    YTEDeclareType(RunInEditor);
    RunInEditor(DocumentedObject *) {}
  };

  class EditableColor : public Attribute
  {
  public:
    YTEDeclareType(EditableColor);
    EditableColor(DocumentedObject *) {}
  };

  class EditorProperty : public Attribute
  {
  public:
    YTEDeclareType(EditorProperty);
    EditorProperty(DocumentedObject *aObject, bool aVisible = true);

    bool mVisible;
  };

  typedef std::vector <std::string> (*StrGettor)(Component*);

  class DropDownStrings : public Attribute
  {
  public:
    YTEDeclareType(DropDownStrings);
    DropDownStrings(DocumentedObject *aObject, StrGettor aStrGettor);

    StrGettor GetStringGettor();

  private:
    StrGettor mStringGettor;
  };
}



