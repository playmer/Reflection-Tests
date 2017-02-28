#pragma once
#include <type_traits>
#include <vector>

#include "CacheOrderedSet.hpp"
#include "Types.hpp"
#include "Reflection.hpp"

template <typename T>
void GenericDestruct(void* aMemory)
{
  (static_cast<T*>(aMemory))->~T();
}

template <typename T>
void GenericDefaultConstruct(void* aMemory)
{
  new (aMemory) T();
}

template <typename T>
void GenericCopyConstruct(void* aObject, void* aMemory)
{
  new (aMemory) T(*static_cast<T*>(aObject));
}

class Type
{
public:
  using DefaultConstructor = void(*)(void*);
  using CopyConstructor = void(*)(void*, void*);
  using Destructor = void(*)(void*);

  template <typename T>
  explicit Type(const char *aName, T *);


  template <typename T>
  explicit Type(T *);

  ~Type();

  const std::string& Name()  const { return mName; }
  size_t             Hash() const { return mHash; }
  size_t             GetAllocatedSize() const { return mAllocatedSize; }
  size_t             GetStoredSize() const { return mStoredSize; }
  DefaultConstructor GetDefaultConstructor() const { return mDefaultConstructor; }
  CopyConstructor    GetCopyConstructor()  const { return mCopyConstructor; }
  Destructor         GetDestructor()  const { return mDestructor; }

  // Don't really need to do this, but w/e.
  bool operator==(const Type &aRight) const
  {
    if ((mHash == aRight.mHash) && (mName == aRight.mName))
    {
      return true;
    }
   
    return false;
  }

  void AddFunction(std::unique_ptr<Function> aFunction);
  void AddProperty(std::unique_ptr<Property> aProperty);

  CacheOrderedSet<std::string, std::unique_ptr<Function>>::range GetFunctionRange(const char *aName)
  {
    std::string name{ aName };
  
    return mFunctions.FindAll(name);
  }

  Function* GetFirstFunction(const char *aName)
  {
    std::string name{ aName };

    return mFunctions.FindFirst(name)->second.get();
  }

  CacheOrderedSet<std::string, std::unique_ptr<Property>>::range GetPropertyRange(const char *aName)
  {
    std::string name{ aName };

    return mProperties.FindAll(name);
  }

  Property* GetFirstProperty(const char *aName)
  {
    std::string name{ aName };

    return mProperties.FindFirst(name)->second.get();
  }

private:
  CacheOrderedSet<std::string, std::unique_ptr<Function>> mFunctions;
  CacheOrderedSet<std::string, std::unique_ptr<Property>> mProperties;
  std::string mName;
  size_t mHash;
  size_t mAllocatedSize;
  size_t mStoredSize;
  DefaultConstructor mDefaultConstructor;
  CopyConstructor mCopyConstructor;
  Destructor mDestructor;
};

#include "Function.hpp"
#include "Property.hpp"
#include "Field.hpp"


template <typename T>
inline Type::Type(const char *aName, T *)
  : mName(aName),
    mHash(std::hash<std::string>{}(mName)),
    mAllocatedSize(sizeof(T)),
    mStoredSize(sizeof(T)),
    mDefaultConstructor(GenericDefaultConstruct<T>),
    mCopyConstructor(GenericCopyConstruct<T>),
    mDestructor(GenericDestruct<T>)
{
}


template <typename T>
inline Type::Type(T *)
  : mName(GetTypeName<T>().data()),
    mHash(std::hash<std::string>{}(mName)),
    mAllocatedSize(sizeof(T)),
    mStoredSize(sizeof(T)),
    mDefaultConstructor(GenericDefaultConstruct<T>),
    mCopyConstructor(GenericCopyConstruct<T>),
    mDestructor(GenericDestruct<T>)
{
}

inline Type::~Type()
{

}

inline void Type::AddFunction(std::unique_ptr<Function> aFunction)
{
  mFunctions.Emplace(aFunction->GetName(), std::move(aFunction));
}

inline void Type::AddProperty(std::unique_ptr<Property> aProperty)
{
  mProperties.Emplace(aProperty->GetName(), std::move(aProperty));
}

template<typename T>
Type* TypeId()
{
  return T::GetStaticType();
}

#define DeclareExternalType(Name) \
namespace Types                   \
{                                 \
  extern Type Name##_Type;        \
}                                 \
                                  \
template <>                       \
inline Type* TypeId<Name>()       \
{                                 \
  return &Types::Name##_Type;     \
}


#define DefineExternalType(Name) \
Type Types::Name##_Type{#Name, static_cast<Name*>(nullptr)};

DeclareExternalType(i8)
DeclareExternalType(i16)
DeclareExternalType(i32)
DeclareExternalType(i64)
DeclareExternalType(u8)
DeclareExternalType(u16)
DeclareExternalType(u32)
DeclareExternalType(u64)
DeclareExternalType(float)
DeclareExternalType(double)

// Used to declare a static type within a class
// Requires DefineType be used at some point in a
// translation unit.
#define DeclareType(Name)     \
static Type sType;            \
static Type* GetStaticType(); \
Type* GetType();

#define DefineType(Name)                                   \
Type Name::sType{#Name, static_cast<Name*>(nullptr)}; \
Type* Name::GetStaticType() { return &sType; };            \
Type* Name::GetType() { return &sType; };



class Base
{
  virtual Type *GetType() = 0;
};