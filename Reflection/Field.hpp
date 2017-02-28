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
    runtime_assert((nullptr != aGetter) && (nullptr != aSetter), 
                   "Both the getter and setter must be set.");
  }
private:
};

