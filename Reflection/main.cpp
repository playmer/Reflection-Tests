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

      int GetX()
      {
        std::cout << "Getting x: " << x << std::endl;
        return x;
      }

      void SetX(int aX)
      {
        std::cout << "Setting x: " << aX <<  std::endl;
        x = aX;
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

  auto test3 = &Test::Test2::UrMum::x;

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

  auto testFunc = BindFunction<decltype(&UrKidClass::Test), &UrKidClass::Test>("Test");
  urKid->AddFunction(std::move(testFunc));

  auto func = BindFunction<decltype(&Test::Test2::UrMum::Print),&Test::Test2::UrMum::Print>("Print");
  auto prop = BindProperty<decltype(&Test::Test2::UrMum::GetX), &Test::Test2::UrMum::GetX,
                           decltype(&Test::Test2::UrMum::SetX), &Test::Test2::UrMum::SetX>("X");
  auto field = BindField<decltype(&Test::Test2::UrMum::y), &Test::Test2::UrMum::y>("Y");

  urMum->AddFunction(std::move(func));
  urMum->AddProperty(std::move(prop));
  urMum->AddField(std::move(field));



  Test::Test2::UrMum mum;
  UrKidClass kid;

  std::cout << "Return: " << urMum->GetFirstFunction("Print")->Invoke(&mum, 1).As<float>() << std::endl;
  auto doesThisWork2 = urKid->GetFirstFunction("Test")->Invoke(&kid);

  auto property = urMum->GetFirstProperty("X");
  property->GetSetter()->Invoke(&mum, 5);
  auto i = property->GetGetter()->Invoke(&mum).As<int>();


  auto fielder = urMum->GetFirstField("Y");
  fielder->GetSetter()->Invoke(&mum, 12);
  auto j = fielder->GetGetter()->Invoke(&mum).As<int>();

}
