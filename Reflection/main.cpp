#include <iostream>
#include "Type.hpp"

namespace Test
{
  namespace Test2
  {
    class Animal
    {
    public:
      DeclareType(Animal)

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

    DefineType(Animal);
  }
}

class Cat
{
public:
  DeclareType(Cat)
  void Test()
  {
    std::cout << "UrKid" << std::endl;
  }
};
DefineType(Cat);

template<typename Woo, typename Boy>
struct TemplatedThing
{

};

namespace FunctionTests
{
  void Func(Cat aStruct) {}
}

int main()
{
  Type test = Type(static_cast<Test::Test2::Animal*>(nullptr));

  auto test3 = &Test::Test2::Animal::x;

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

  auto animalType = Test::Test2::Animal::GetStaticType();
  auto catType = Cat::GetStaticType();

  auto testFunc = BindFunction<decltype(&Cat::Test), &Cat::Test>("Test");
  catType->AddFunction(std::move(testFunc));

  auto func = BindFunction<decltype(&Test::Test2::Animal::Print),&Test::Test2::Animal::Print>("Print");
  auto prop = BindProperty<decltype(&Test::Test2::Animal::GetX), &Test::Test2::Animal::GetX,
                           decltype(&Test::Test2::Animal::SetX), &Test::Test2::Animal::SetX>("X");
  auto field = BindField<decltype(&Test::Test2::Animal::y), &Test::Test2::Animal::y>("Y");

  animalType->AddFunction(std::move(func));
  animalType->AddProperty(std::move(prop));
  animalType->AddField(std::move(field));



  Test::Test2::Animal animal;
  Cat cat;

  std::cout << "Return: " << animalType->GetFirstFunction("Print")->Invoke(&animal, 1).As<float>() << std::endl;
  auto doesThisWork2 = catType->GetFirstFunction("Test")->Invoke(&cat);

  auto property = animalType->GetFirstProperty("X");
  property->GetSetter()->Invoke(&animal, 5);
  auto i = property->GetGetter()->Invoke(&animal).As<int>();


  auto fielder = animalType->GetFirstField("Y");
  fielder->GetSetter()->Invoke(&animal, 12);
  auto j = fielder->GetGetter()->Invoke(&animal).As<int>();

}
