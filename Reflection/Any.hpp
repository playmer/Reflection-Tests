#pragma once

#include "Types.hpp"
#include "Type.hpp"


class Any
{
public:

  template <typename ...Arguments>
  static std::vector<Any> FromVariadic(Arguments...aArguments);
  
  Any()
  {
    mType = nullptr;
    memset(mData, 0, sizeof(mData));
  }

  Any(void* object, Type* type)
  {
    mType = type;
    byte* data = AllocateData(type->GetStoredSize());
    type->GetCopyConstructor()(object, data);
  }

  void ConstructFrom(void* object, Type* type)
  {
    Clear();
    mType = type;
    byte* data = AllocateData(type->GetStoredSize());
    type->GetCopyConstructor()(object, data);
  }

  template <typename T>
  explicit Any(const T& value)
  {
    mType = TypeId<T>();
    byte* data = AllocateData(sizeof(T));
    new (data) T(value);
  }

  byte* AllocateData(size_t size)
  {
    if (size <= sizeof(mData))
    {
      return mData;
    }

    auto data = new byte[size];
    new (mData) byte*(data);
    return data;
  }

  byte* GetData()
  {
    if (mType->GetStoredSize() <= sizeof(mData))
    {
      return mData;
    }

    return *reinterpret_cast<byte**>(mData);
  }

  void Clear()
  {
    if ((nullptr == mType) || (nullptr == mType->GetDestructor()))
    {
      return;
    }

    byte* data = GetData();
    mType->GetDestructor()(data);

    if (mType->GetStoredSize() > sizeof(mData))
    {
      delete data;
    }

    mType = nullptr;
    memset(mData, 0, sizeof(mData));
  }

  ~Any()
  {
    Clear();
  }

  template <typename T>
  bool IsType()
  {
    auto type = TypeId<T>();
    auto truth = mType == type;
    return truth;
  }

  template <typename T>
  T& As()
  {
    runtime_assert(IsType<T>(), "This Any is being casted into the incorrect type.");

    return *reinterpret_cast<T*>(GetData());
  }

  Type* mType;
  byte mData[16];
};





template <typename... Rest> struct ParseAndAddArguments;

template <>
struct ParseAndAddArguments<>
{
  inline static void Parse(std::vector<Any> &aArguments)
  {
  }
};

template <typename First, typename... Rest>
struct ParseAndAddArguments<First, Rest...>
{
  inline static void Parse(std::vector<Any> &aArguments, First aFirst, Rest ...aRest)
  {
    aArguments.emplace_back(aFirst);
    ParseAndAddArguments<Rest...>::Parse(aArguments, aRest...);
  }
};

template <typename ...Arguments>
std::vector<Any> Any::FromVariadic(Arguments...aArguments)
{
  std::vector<Any> arguments;
  ParseAndAddArguments<Arguments...>::Parse(arguments, aArguments...);

  return arguments;
}
