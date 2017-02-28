#pragma once

#include "Function.hpp"

// TODO: Have some requirements on the types of setters and getters.
class Property
{
public:
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
private:
  std::string mName;
  std::unique_ptr<Function> mGetter;
  std::unique_ptr<Function> mSetter;
};