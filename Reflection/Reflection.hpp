#pragma once

#include "ConstexprString.hpp"

#define CONSTEXPR_FUNCTION_SIGNATURE __FUNCSIG__

constexpr size_t GetTypeStart(const char *aTypeNameString)
{
  size_t beginTrim = 0;

#if defined(__clang__)
  beginTrim = 46;
#elif defined(_MSC_VER)
  if (*(aTypeNameString + 39) == 's') // Where class or struct appears in MSVC
  {
    beginTrim = 46; //Where typename begins appearing in MSVC if struct.
  }
  else
  {
    beginTrim = 45; //Where typename begins appearing in MSVC if class.
  }
#endif

  return beginTrim;
}

constexpr size_t GetTypeEnd()
{
  size_t endTrim = 0;

#if defined(__clang__)
  endTrim = 1;
#elif defined(_MSC_VER)
  endTrim = 7;
#endif

  return endTrim;
}

template <typename T, T aFunction>
constexpr auto GetFunctionSignature()
{
  constexpr const char* typeName = CONSTEXPR_FUNCTION_SIGNATURE;

  constexpr size_t required_length = StringLength(typeName);
  ConstexprToken<required_length> test{ typeName };

  return test;
}

constexpr bool IsWhiteSpace(char aCharacter)
{
  if ((9 >= aCharacter) && (aCharacter <= 13) || ' ' == aCharacter)
  {
    return true;
  }

  return false;
}

constexpr StringRange GetTypeNameRange(const char *aStart, size_t aTotalSize)
{
  // Find first token of the Type name.
  auto it = aStart;

  while (IsWhiteSpace(*it))
  {
    ++it;
  }

  constexpr const char *begin = it;
  constexpr const char *firstKeywordStart = it;

  while((false == IsWhiteSpace(*it)) && (it < (aStart + aTotalSize)))
  {
    ++it;
  }

  constexpr StringRange firstKeyword{ firstKeywordStart, it };
  constexpr StringRange structName{ "struct" };
  constexpr StringRange className{ "class" };

  if ((firstKeyword == structName) || (firstKeyword == className))
  {
    
  }
}

template <typename T>
constexpr auto GetTypeName()
{
  constexpr const char* typeName = CONSTEXPR_FUNCTION_SIGNATURE;

  constexpr size_t totalLength = StringLength(typeName);

  // TODO: Should also work for GCC.
#if defined(__clang__)
  constexpr size_t lastSpace = GetLastInstanceOfCharacter(typeName, StringLength(typeName), '=');
  constexpr size_t typeNameLength = totalLength - lastSpace - GetTypeEnd() - 2;

  ConstexprToken<typeNameLength> token{ typeName + lastSpace + 2 };
#elif defined(_MSC_VER)
  constexpr size_t firstArrow = GetFirstInstanceOfCharacter(typeName, StringLength(typeName), '<');
  constexpr size_t lastArrow = GetLastInstanceOfCharacter(typeName, StringLength(typeName), '>');

  constexpr size_t typenameTotalRangeSize = lastArrow - firstArrow;
  constexpr auto typenameRange = GetTypeNameRange(typeName, typenameTotalRangeSize);

  // TODO: Remove struct and class keywords from templated output.
  ConstexprToken<typenameRange.Size()> token{ typenameRange.mBegin};
#endif

  return token;

  //ConstexprToken<totalLength> token2{ typeName};
  //return token2;
}