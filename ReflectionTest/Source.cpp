#include <array>

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
  {
    for (size_t i = 0; i < Size; i++)
    {
      mData[i] = aBegin[i];
    }
    
    mData[Size] = '\0';
  }

  constexpr void Copy(const char *aBegin)
  {
    //for (size_t i = 0; i < Size; i++)
    //{
    //  mData[i] = aBegin[i];
    //}
    //
    //mData[Size] = '\0';
  }


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
  //size_t beginTrim = GetTypeStart(typeName);

  constexpr size_t required_length = StringLength(typeName);
  ConstexprToken<required_length> test{ typeName };
  //const char *fullTypeName = typeName;

  return test;
}

template <typename T>
constexpr auto GetTypeName()
{
  constexpr const char* typeName = CONSTEXPR_FUNCTION_SIGNATURE;
  //constexpr size_t required_length = StringLength(typeName) - 7;
  //constexpr size_t test = StringLength(typeName) + 1;

  //int endTrim = 5;
  

  //size_t beginTrim = GetTypeStart(typeName);
  //if (*(typeName + 39) == 's') // Where class or struct appears in MSVC
  //{
  //  beginTrim = 46; //Where typename begins appearing in MSVC if struct.
  //}
  //else
  //{
  //  beginTrim = 45; //Where typename begins appearing in MSVC if class.
  //}

  //const char *fullTypeName = typeName + beginTrim;
  const char *fullTypeName = typeName;

  //for (size_t i = 0; i < required_length; ++i)
  //{
  //  toReturn[i] = *(fullTypeName + i);
  //}

  //toReturn[required_length + 1] = '\0';

  return fullTypeName;
}

void Func1(UrKidStruct aStruct) {}
void Func2(UrKidClass aStruct) {}

int main()
{
  constexpr const char *doesThisWork = GetTypeName<Test::Test2::UrMum>();
  printf("%s\n", GetTypeName<Test::Test2::UrMum>());
  printf("%s\n", GetTypeName<Test::UrSun>());
  printf("%s\n", GetTypeName<UrKidClass>());

  constexpr size_t required_length = StringLength(GetTypeName<UrKidClass>());
  printf("%d\n", required_length);
  printf("%s\n", GetTypeName<UrKidStruct>());

  constexpr auto func1 = GetFunctionSignature<decltype(Func1)*, Func1>();
  //constexpr auto func2 = GetFunctionSignature<decltype(Func2)*, Func2>();
  printf("%s\n", func1.mData);
  //printf("%s\n", func2.mData);
}