#include <iostream>
#include "Type.hpp"

namespace Test
{
  namespace Test2
  {
    class UrMum
    {
    public:
      DeclareType(UrMum)

      float Print(int)
      {
        std::cout << x << " " << y << " " << z << " " << w << " " << std::endl;
        return 42.0f;
      }

      int x = 0;
      int y = 1;
      int z = 2;
      int w = 3;

    };

    DefineType(UrMum);
  }

  class UrSun {};
}

struct UrKidStruct {};

class UrKidClass
{
public:
  DeclareType(UrKidClass)
  void Test()
  {
    std::cout << "UrKid" << std::endl;
  }
};
DefineType(UrKidClass);

template<typename Woo, typename Boy>
struct TemplatedThing
{

};

namespace FunctionTests
{
  void Func1(UrKidStruct aStruct) {}
  void Func2(UrKidClass aStruct) {}
}

int main()
{
  Type test = Type(static_cast<Test::Test2::UrMum*>(nullptr));

  auto i8test = TypeId<i8>();
  auto i16test = TypeId<i16>();
  auto i32test = TypeId<i32>();
  auto i64test = TypeId<i64>();
  auto u8test =  TypeId<u8>();
  auto u16test = TypeId<u16>();
  auto u32test = TypeId<u32>();
  auto u64test = TypeId<u64>();
  auto floattest = TypeId<float>();
  auto doubletest = TypeId<double>();

  auto urMum = Test::Test2::UrMum::GetStaticType();
  auto urKid = UrKidClass::GetStaticType();

  auto testFunc = Binding<decltype(&UrKidClass::Test)>::BindFunction<&UrKidClass::Test>("Test");
  urKid->AddFunction(std::move(testFunc));

  auto func = Binding<decltype(&Test::Test2::UrMum::Print)>::BindFunction<&Test::Test2::UrMum::Print>("Print");
  urMum->AddFunction(std::move(func));

  Test::Test2::UrMum mum;
  UrKidClass kid;

  auto printRange = urMum->GetFirstFunction("Print");
  auto testRange = urKid->GetFirstFunction("Test");

  std::vector<Any> args;
  args.emplace_back(Any(mum));
  args.emplace_back(Any(1));


  std::vector<Any> args2;
  args2.emplace_back(Any(kid));

  auto doesThisWork = printRange->Invoke(args);
  std::cout << "Return: " << doesThisWork.As<float>();

  auto doesThisWork2 = testRange->Invoke(args2);

  //constexpr auto doesThisWork = GetTypeName<Test::Test2::UrMum>();
  //std::cout << doesThisWork.data() << std::endl;
  //std::cout << GetTypeName<Test::UrSun>().data() << std::endl;
  //std::cout << GetTypeName<UrKidClass>().data() << std::endl;
  //std::cout << GetTypeName<UrKidStruct>().data() << std::endl;
  //std::cout << GetTypeName<TemplatedThing<UrKidClass, UrKidStruct>>().data() << std::endl;
  //
  //
  //constexpr ConstexprToken<64> copyTest{doesThisWork};
  //std::cout << "Copying works: " << copyTest.data() << std::endl;
  //
  //constexpr auto func1 = GetFunctionSignature<decltype(FunctionTests::Func1)*, FunctionTests::Func1>();
  ////constexpr auto func2 = GetFunctionSignature<decltype(Func2)*, Func2>();
  //std::cout << func1.data() << std::endl;
  ////printf("%s\n", func2.mData);
}