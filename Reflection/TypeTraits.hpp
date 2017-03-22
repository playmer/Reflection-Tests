#pragma once

#include "Utilities.hpp"

template<typename T>
inline size_t SizeOf()
{
  return sizeof(T);
}

template<>
inline size_t SizeOf<void>()
{
  return 0;
}


template <typename T>
inline void GenericDestruct(void* aMemory)
{
  (static_cast<T*>(aMemory))->~T();
}

template <typename T, typename Enable = void>
struct GenericDefaultConstructStruct
{

};

template <typename T>
struct GenericDefaultConstructStruct<T, typename std::enable_if<std::is_default_constructible<T>::value == false>::type>
{
  static inline void DefaultConstruct(void *aMemory)
  {
    runtime_assert(false, "Trying to default construct something without a default constructor.");
  }
};

template <typename T>
struct GenericDefaultConstructStruct<T, typename std::enable_if<std::is_default_constructible<T>::value>::type>
{
  static inline void DefaultConstruct(void *aMemory)
  {
    new (aMemory) T();
  }
};


template <typename T, typename Enable = void>
struct GenericCopyConstructStruct
{

};

template <typename T>
struct GenericCopyConstructStruct<T, typename std::enable_if<std::is_copy_constructible<T>::value == false>::type>
{
  static inline void CopyConstruct(void *aObject, void *aMemory)
  {
    runtime_assert(false, "Trying to copy construct something without a copy constructor.");
  }
};

template <typename T>
struct GenericCopyConstructStruct<T, typename std::enable_if<std::is_copy_constructible<T>::value>::type>
{
  static inline void CopyConstruct(void *aObject, void *aMemory)
  {
    new (aMemory) T(*static_cast<T*>(aObject));
  }
};

template <typename T>
inline void GenericDefaultConstruct(void *aMemory)
{
  GenericDefaultConstructStruct<T>::DefaultConstruct(aMemory);
}

template <typename T>
inline void GenericCopyConstruct(void* aObject, void* aMemory)
{
  GenericCopyConstructStruct<T>::CopyConstruct(aObject, aMemory);
}


template <>
inline void GenericDestruct<void>(void* aMemory)
{
}

template <>
inline void GenericDefaultConstruct<void>(void* aMemory)
{
}

template <>
inline void GenericCopyConstruct<void>(void* aObject, void* aMemory)
{
}

template <typename T>
struct Identity
{
  T operator()(T x) const { return x; }
};


template<typename T>
struct remove_all_pointers : std::conditional_t<std::is_pointer_v<T>,
  remove_all_pointers<std::remove_pointer_t<T>>,
  Identity<T>>
{
};

template<typename T>
using remove_all_pointers_t = typename remove_all_pointers<T>::type;



template <typename Return, typename Arg = Return>
struct DecomposeFieldPointer {};

template <typename Object, typename Field>
struct DecomposeFieldPointer<Field Object::*>
{
  using ObjectType = Object;
  using FieldType = Field;
};


template <typename Return, typename Arg = Return>
struct DecomposeFunctionType {};

template <typename Return, typename Event>
struct DecomposeFunctionType<Return(*)(Event*)>
{
  using ReturnType = Return;
  using EventType = Event;
};

template <typename Return, typename Object, typename Event>
struct DecomposeFunctionType<Return(Object::*)(Event*)>
{
  using ReturnType = Return;
  using ObjectType = Object;
  using EventType = Event;
};

// Helper to call the constructor of a type.
inline void GenericDoNothing(byte *aMemory)
{
}

