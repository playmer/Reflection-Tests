#include <array>
#include <iostream>

#define CONSTEXPR_FUNCTION_SIGNATURE __FUNCSIG__

constexpr size_t StringLength(const char *aString)
{
  size_t i = 0;

  while (*aString != NULL)
  {
    ++i;
    ++aString;
  }

  return i;
}

namespace Test
{
  namespace Test2
  {
    class UrMum {};
  }

  class UrSun {};
}

struct UrKidStruct {};

class UrKidClass {};

template <size_t Size>
struct ConstexprToken
{
  constexpr ConstexprToken(const char *aBegin)
    : mData{'0'}
  {
    for (size_t i = 0; i < Size; i++)
    {
      mData[i] = aBegin[i];
    }

    mData[Size] = '\0';
  }

  constexpr const char* Data() const { return mData; };
  constexpr const char* data() const { return mData; };

private:
  char mData[Size + 1];
};

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

template <typename T>
constexpr auto GetTypeName()
{
  constexpr const char* typeName = CONSTEXPR_FUNCTION_SIGNATURE;

  const char *fullTypeName = typeName;

  constexpr size_t required_length = StringLength(typeName);
  ConstexprToken<required_length> test{ typeName };

  return fullTypeName;
}

void Func1(UrKidStruct aStruct) {}
void Func2(UrKidClass aStruct) {}

int main()
{
  constexpr const char *doesThisWork = GetTypeName<Test::Test2::UrMum>();
  std::cout << doesThisWork << std::endl;
  std::cout << GetTypeName<Test::UrSun>() << std::endl;
  std::cout << GetTypeName<UrKidClass>() << std::endl;

  constexpr size_t required_length = StringLength(GetTypeName<UrKidClass>());
  std::cout << required_length << std::endl;
  std::cout << GetTypeName<UrKidStruct>() << std::endl;

  constexpr auto func1 = GetFunctionSignature<decltype(Func1)*, Func1>();
  //constexpr auto func2 = GetFunctionSignature<decltype(Func2)*, Func2>();
  std::cout << func1.data() << std::endl;
  //printf("%s\n", func2.mData);
}