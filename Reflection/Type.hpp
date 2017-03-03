#pragma once
#include <type_traits>
#include <vector>

#include "CacheOrderedSet.hpp"
#include "Types.hpp"
#include "Reflection.hpp"


class Type
{
public:
  using DefaultConstructor = void(*)(void*);
  using CopyConstructor = void(*)(void*, void*);
  using Destructor = void(*)(void*);
  
  template <typename T>
  explicit Type(const char *aName, T *aNull);


  template <typename T>
  explicit Type(T *aNull);

  template <typename T>
  explicit Type(Type *aType, bool aReference, T *aNull);

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
  void AddField(std::unique_ptr<Field>    aField);

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


  CacheOrderedSet<std::string, std::unique_ptr<Property>>::range GetFieldRange(const char *aName)
  {
    std::string name{ aName };

    return mFields.FindAll(name);
  }

  Property* GetFirstField(const char *aName)
  {
    std::string name{ aName };

    return mFields.FindFirst(name)->second.get();
  }

  Type* GetPointerTo()
  {
    return mPointerTo;
  }

  Type* GetReferenceTo()
  {
    return mPointerTo;
  }

private:
  CacheOrderedSet<std::string, std::unique_ptr<Function>> mFunctions;
  CacheOrderedSet<std::string, std::unique_ptr<Property>> mProperties;
  CacheOrderedSet<std::string, std::unique_ptr<Property>> mFields;
  std::string mName;
  size_t mHash;
  size_t mAllocatedSize;
  size_t mStoredSize;
  DefaultConstructor mDefaultConstructor;
  CopyConstructor mCopyConstructor;
  Destructor mDestructor;

  Type *mPointerTo;
  Type *mReferenceTo;
};

template<typename T>
struct TypeIdentification
{
  static inline Type* TypeId()
  {
    return T::GetStaticType();
  }
};


template<typename T>
inline Type* TypeId();

template<typename T>
struct TypeIdentification<T*>
{
  static inline Type* TypeId()
  {
    static Type type = Type{ ::TypeId<T>(), false, static_cast<T*>(nullptr) };
    
    return &type;
  }
};

template<typename T>
struct TypeIdentification<T&>
{
  static inline Type* TypeId()
  {
    static Type type = Type{ ::TypeId<T>(), true, static_cast<T*>(nullptr) };

    return &type;
  }
};


template<typename T>
inline Type* TypeId()
{
  return TypeIdentification<T>::TypeId();
}

#define DeclareExternalType(Name)   \
namespace Types                     \
{                                   \
  extern Type Name##_Type;          \
}                                   \
                                    \
                                    \
template<>                          \
struct TypeIdentification<Name>     \
{                                   \
  static inline Type* TypeId()      \
  {                                 \
    return &Types::Name##_Type;     \
  }                                 \
};


#define DefineExternalType(Name) \
Type Types::Name##_Type{#Name, static_cast<Name*>(nullptr)};

DeclareExternalType(void)
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


#include "Function.hpp"
#include "Property.hpp"
#include "Field.hpp"


template <typename T>
inline Type::Type(const char *aName, T *)
  : mName(aName),
    mHash(std::hash<std::string>{}(mName)),
    mAllocatedSize(SizeOf<T>()),
    mStoredSize(SizeOf<T>()),
    mDefaultConstructor(GenericDefaultConstruct<T>),
    mCopyConstructor(GenericCopyConstruct<T>),
    mDestructor(GenericDestruct<T>)
{
}


template <typename T>
inline Type::Type(T *)
  : mName(GetTypeName<T>().data()),
    mHash(std::hash<std::string>{}(mName)),
    mAllocatedSize(SizeOf<T>()),
    mStoredSize(SizeOf<T>()),
    mDefaultConstructor(GenericDefaultConstruct<T>),
    mCopyConstructor(GenericCopyConstruct<T>),
    mDestructor(GenericDestruct<T>)
{
}


template <typename T>
inline Type::Type(Type *aType, bool aReference, T *aNull)
  : mName(GetTypeName<T>().data()),
    mHash(std::hash<std::string>{}(mName)),
    mAllocatedSize(SizeOf<T>()),
    mStoredSize(SizeOf<T>()),
    mDefaultConstructor(GenericDefaultConstruct<T>),
    mCopyConstructor(GenericCopyConstruct<T>),
    mDestructor(GenericDestruct<T>)
{
  if (aReference)
  {
    mReferenceTo = aType;
  }
  else
  {
    mPointerTo = aType;
  }
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

inline void Type::AddField(std::unique_ptr<Field> aField)
{
  mFields.Emplace(aField->GetName(), std::move(aField));
}
