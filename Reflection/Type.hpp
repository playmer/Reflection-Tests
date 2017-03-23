#pragma once
#include <type_traits>
#include <vector>

#include "OrderedMultiMap.hpp"
#include "ForwardDeclarations.hpp"
#include "Utilities.hpp"
#include "Reflection.hpp"

class Type;

class Base
{
  virtual Type *GetType() = 0;
};



template <typename T>
typename T::SelfType GetSelfType(typename T::SelfType*) {}

template <typename T>
void GetSelfType(...) {}


template <typename T>
T GetDummy(void (T::*)());



// Used to declare a static type within a class
// Requires DefineType be used at some point in a
// translation unit.
#define DeclareType(Name)                                      \
void Dummy() {}                                                \
typedef decltype(GetDummy(&Name::Dummy)) TempSelfType;         \
typedef decltype(GetSelfType<TempSelfType>(nullptr)) BaseType; \
typedef TempSelfType SelfType;                                 \
static Type sType;                                             \
static Type* GetStaticType() { return &sType; };               \
Type* GetType() { return &sType; };                            \
static void InitializeType();


#define DefineType(Name)                                 \
Type Name::sType{#Name,                                  \
                 static_cast<Name*>(nullptr),            \
                 static_cast<Name::BaseType*>(nullptr)}; \
void Name::InitializeType()



class DocumentedObject : public Base
{
public:
  DeclareType(DocumentedObject);

  DocumentedObject()
    : mDocumentation("")
  {

  }


  DocumentedObject(const char *aDocumentation)
    : mDocumentation(aDocumentation)
  {

  }

  std::string GetDocumentation()
  {
    return mDocumentation;
  }

  void SetDocumentation(const char *aString)
  {
    mDocumentation = aString;
  }
private:
  std::string mDocumentation;
};

class Type : public DocumentedObject
{
public:
  DeclareType(Type)

  using DefaultConstructor = void(*)(void*);
  using CopyConstructor = void(*)(void*, void*);
  using Destructor = void(*)(void*);

  enum class Modifier
  {
    Normal,
    Reference,
    Pointer,
    Const
  };

  template <typename tType>
  explicit Type(const char *aName, tType *aNull);

  template <typename tDerived, typename tBase>
  explicit Type(const char *aName, tDerived *aDerivedNull, tBase *aBaseNull);


  template <typename tDerived, typename tBase>
  explicit Type(tDerived *aDerivedNull, tBase *aBaseNull);

  template <typename T>
  explicit Type(Type *aType, Modifier aModifier, T *aNull);

  template <typename T>
  explicit Type(Type *aType, Modifier aModifier, T *aNull, bool aFalse);

  Type(Type&) = delete;

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

  OrderedMultiMap<std::string, std::unique_ptr<Function>>::range GetFunctionRange(const char *aName)
  {
    std::string name{ aName };
  
    return mFunctions.FindAll(name);
  }

  Function* GetFirstFunction(const char *aName)
  {
    std::string name{ aName };

    return mFunctions.FindFirst(name)->second.get();
  }

  OrderedMultiMap<std::string, std::unique_ptr<Property>>::range GetPropertyRange(const char *aName)
  {
    std::string name{ aName };

    return mProperties.FindAll(name);
  }

  Property* GetFirstProperty(const char *aName)
  {
    std::string name{ aName };

    return mProperties.FindFirst(name)->second.get();
  }


  OrderedMultiMap<std::string, std::unique_ptr<Property>>::range GetFieldRange(const char *aName)
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
    return mReferenceTo;
  }

  Type* GetBaseType()
  {
    return mBaseType;
  }

private:
  OrderedMultiMap<std::string, std::unique_ptr<Function>> mFunctions;
  OrderedMultiMap<std::string, std::unique_ptr<Property>> mProperties;
  OrderedMultiMap<std::string, std::unique_ptr<Property>> mFields;
  std::string mName;
  size_t mHash;
  size_t mAllocatedSize;
  size_t mStoredSize;
  DefaultConstructor mDefaultConstructor;
  CopyConstructor mCopyConstructor;
  Destructor mDestructor;

  Type *mReferenceTo;
  Type *mPointerTo;
  Type *mConstOf;
  Type *mBaseType;
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
inline void InitializeType();

template<typename T>
struct TypeIdentification<T*>
{
  static inline Type* TypeId()
  {
    static Type type{ ::TypeId<T>(), Type::Modifier::Pointer, static_cast<T**>(nullptr) };
    
    return &type;
  }
};

template<typename T>
struct TypeIdentification<T&>
{
  static inline Type* TypeId()
  {
    static Type type{ ::TypeId<T>(), Type::Modifier::Reference, static_cast<T*>(nullptr), false };

    return &type;
  }
};


template<typename T>
struct TypeIdentification<const T>
{
  static inline Type* TypeId()
  {
    static Type type{ ::TypeId<T>(), Type::Modifier::Const, static_cast<const T*>(nullptr) };

    return &type;
  }
};


template<typename T>
inline Type* TypeId()
{
  return TypeIdentification<T>::TypeId();
}

//template<typename T>
//inline void InitializeType()
//{
//  return TypeInitialization<T>::InitializeType();
//}

#define DeclareExternalType(Name)                    \
template<>                                           \
struct TypeIdentification<Name>                      \
{                                                    \
  static inline Type* TypeId()                       \
  {                                                  \
    static Type type{ #Name,                         \
                      static_cast<Name*>(nullptr) }; \
    return &type;                                    \
  }                                                  \
};


#define DefineExternalType(Name)

DeclareExternalType(void)
DeclareExternalType(s8)
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
DeclareExternalType(std::string)


#include "Function.hpp"
#include "Property.hpp"
#include "Field.hpp"


template <typename tDerived, typename tBase>
inline Type::Type(const char *aName, tDerived *, tBase *)
  : mName(aName),
    mHash(std::hash<std::string>{}(mName)),
    mAllocatedSize(SizeOf<tDerived>()),
    mStoredSize(SizeOf<tDerived>()),
    mDefaultConstructor(GenericDefaultConstruct<tDerived>),
    mCopyConstructor(GenericCopyConstruct<tDerived>),
    mDestructor(GenericDestruct<tDerived>),
    mReferenceTo(nullptr),
    mPointerTo(nullptr),
    mConstOf(nullptr),
    mBaseType(TypeId<tBase>())
{
}

template <typename tType>
inline Type::Type(const char *aName, tType *)
  : mName(aName),
  mHash(std::hash<std::string>{}(mName)),
  mAllocatedSize(SizeOf<tType>()),
  mStoredSize(SizeOf<tType>()),
  mDefaultConstructor(GenericDefaultConstruct<tType>),
  mCopyConstructor(GenericCopyConstruct<tType>),
  mDestructor(GenericDestruct<tType>),
  mReferenceTo(nullptr),
  mPointerTo(nullptr),
  mConstOf(nullptr),
  mBaseType(nullptr)
{
}


template <typename tDerived, typename tBase>
inline Type::Type(tDerived *, tBase *)
  : mName(GetTypeName<tDerived>().data()),
    mHash(std::hash<std::string>{}(mName)),
    mAllocatedSize(SizeOf<tDerived>()),
    mStoredSize(SizeOf<tDerived>()),
    mDefaultConstructor(GenericDefaultConstruct<tDerived>),
    mCopyConstructor(GenericCopyConstruct<tDerived>),
    mDestructor(GenericDestruct<tDerived>),
    mReferenceTo(nullptr),
    mPointerTo(nullptr),
    mConstOf(nullptr), 
    mBaseType(TypeId<tBase>())
{
}




template <typename T>
inline Type::Type(Type *aType, Modifier aModifier, T *aNull)
  : mName(GetTypeName<T>().data()),
    mHash(std::hash<std::string>{}(mName)),
    mAllocatedSize(SizeOf<T>()),
    mStoredSize(SizeOf<T>()),
    mDefaultConstructor(GenericDefaultConstruct<T>),
    mCopyConstructor(GenericCopyConstruct<T>),
    mDestructor(GenericDestruct<T>),
    mReferenceTo(nullptr),
    mPointerTo(nullptr),
    mConstOf(nullptr),
    mBaseType(nullptr)
{
  switch (aModifier)
  {
    case Modifier::Const:
    {
      mConstOf = aType;
      break;
    }
    case Modifier::Reference:
    {
      mReferenceTo = aType;
      break;
    }
    case Modifier::Pointer:
    {
      mPointerTo = aType;
      break;
    }
    case Modifier::Normal:
    default:
      break;
  }
}

template <typename T>
inline Type::Type(Type *aType, Modifier aModifier, T *aNull, bool aFalse)
  : mName(GetTypeName<T&>().data()),
    mHash(std::hash<std::string>{}(mName)),
    mAllocatedSize(SizeOf<T*>()),
    mStoredSize(SizeOf<T*>()),
    mDefaultConstructor(GenericDefaultConstruct<T*>),
    mCopyConstructor(GenericCopyConstruct<T*>),
    mDestructor(GenericDestruct<T*>),
    mReferenceTo(nullptr),
    mPointerTo(nullptr),
    mConstOf(nullptr),
    mBaseType(nullptr)
{
  switch (aModifier)
  {
    case Modifier::Const:
    {
      mConstOf = aType;
      break;
    }
    case Modifier::Reference:
    {
      mReferenceTo = aType;
      break;
    }
    case Modifier::Pointer:
    {
      mPointerTo = aType;
      break;
    }
    case Modifier::Normal:
    default:
      break;
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
