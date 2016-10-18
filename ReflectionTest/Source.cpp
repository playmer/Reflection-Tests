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

template <size_t ConstSize>
struct ConstexprToken
{
  constexpr ConstexprToken(const char *aBegin)
    : mData{'0'}
  {
    for (size_t i = 0; i < ConstSize; i++)
    {
      mData[i] = aBegin[i];
    }

    mData[ConstSize] = '\0';
  }

  constexpr size_t Size() const { return ConstSize; };
  constexpr size_t size() const { return ConstSize; };
  constexpr const char* Data() const { return mData; };
  constexpr const char* data() const { return mData; };

private:
  char mData[ConstSize + 1];
};


constexpr size_t GetLastInstanceOfCharacter(const char *aTypeNameString, size_t aSize, char aCharacter)
{
  size_t toReturn = aSize + 1;

  while (aSize != 0)
  {
    if (aTypeNameString[aSize] == aCharacter)
    {
      toReturn = aSize;
      break;
    }
    --aSize;
  }

  return toReturn;
}


constexpr size_t GetFirstInstanceOfCharacter(const char *aTypeNameString, size_t aSize, char aCharacter)
{
  size_t toReturn = aSize + 1;

  size_t i = 0;

  while (i != aSize)
  {
    if (aTypeNameString[aSize] == aCharacter)
    {
      toReturn = aSize;
      break;
    }
    ++i;
  }

  return toReturn;
}

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

  constexpr size_t totalLength = StringLength(typeName);
  constexpr size_t lastSpace = GetLastInstanceOfCharacter(typeName, StringLength(typeName), ' ');
  constexpr size_t typeNameLength = totalLength - lastSpace - GetTypeEnd() - 1;

  ConstexprToken<typeNameLength> token{ typeName + lastSpace + 1 };

  return token;
}

namespace Function
{
  void Func1(UrKidStruct aStruct) {}
  void Func2(UrKidClass aStruct) {}
}

int main()
{
  constexpr auto doesThisWork = GetTypeName<Test::Test2::UrMum>();
  std::cout << doesThisWork.data() << std::endl;
  std::cout << GetTypeName<Test::UrSun>().data() << std::endl;
  std::cout << GetTypeName<UrKidClass>().data() << std::endl;

  constexpr size_t required_length = GetTypeName<UrKidClass>().Size();
  std::cout << required_length << std::endl;
  std::cout << GetTypeName<UrKidStruct>().data() << std::endl;

  constexpr auto func1 = GetFunctionSignature<decltype(Function::Func1)*, Function::Func1>();
  //constexpr auto func2 = GetFunctionSignature<decltype(Func2)*, Func2>();
  std::cout << func1.data() << std::endl;
  //printf("%s\n", func2.mData);
}