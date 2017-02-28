//////////////////////////////////////////////
// Author: Joshua T. Fisher
//////////////////////////////////////////////
#pragma once

#ifndef Types_hpp
#define Types_hpp

#include <stdint.h>

#include <memory>
#include <string>
#include <unordered_map>

using byte = std::uint8_t;

using i8 =  std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

using u8  = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

class Function;
class Property;
class Field;

// The fact that I actually have to do this makes me sick.
using namespace std::string_literals;

// Helper to call the constructor of a type.
inline void GenericDoNothing(byte *aMemory)
{
}

inline void runtime_assert(bool aValue, const char *aMessage = "")
{
  if (false == aValue)
  {
    printf("ASSERT: %s\n", aMessage);

    // Purposely ruining this programs life.
    int *base = nullptr;
    *base = 1;
  }
}

enum class StringComparison
{
  String1Null,     // (We check this first)
  LesserInString1, // The first character that does not match has a lower value in ptr1 than in ptr2
  Equal,
  GreaterInString1,// The first character that does not match has a greater value in ptr1 than in ptr2
  String2Null,     // (We check this Second)
};

inline StringComparison StringCompare(const char *aLeft, const char *aRight)
{
  if (nullptr == aLeft)
  {
    return StringComparison::String1Null;
  }

  if (nullptr == aRight)
  {
    return StringComparison::String2Null;
  }

  auto comparison = std::strcmp(aLeft, aRight);

  if (0 == comparison)
  {
    return StringComparison::Equal;
  }
  else if (comparison < 0)
  {
    return StringComparison::LesserInString1;
  }
  else // if (comparison < 0) This is by definition of the domain, no need to check
  {
    return StringComparison::GreaterInString1;
  }
}

#endif