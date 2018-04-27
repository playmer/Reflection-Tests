#pragma once
#include "Type.hpp"

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
}



