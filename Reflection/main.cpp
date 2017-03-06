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

    DefineType(Animal)
    {
      auto print = BindFunction<decltype(&Test::Test2::Animal::Print), &Test::Test2::Animal::Print>("Print");
      auto xProp = BindProperty<decltype(&Test::Test2::Animal::GetX), &Test::Test2::Animal::GetX,
                                decltype(&Test::Test2::Animal::SetX), &Test::Test2::Animal::SetX>("X");

      GetStaticType()->AddFunction(std::move(print));
      GetStaticType()->AddProperty(std::move(xProp));

      auto x = BindField<decltype(&Test::Test2::Animal::x), 
                                  &Test::Test2::Animal::x>("X");
      auto y = BindField<decltype(&Test::Test2::Animal::y), 
                                  &Test::Test2::Animal::y>("Y");
      auto z = BindField<decltype(&Test::Test2::Animal::z), 
                                  &Test::Test2::Animal::z>("Z");
      auto w = BindField<decltype(&Test::Test2::Animal::w), 
                                  &Test::Test2::Animal::w>("W");

      GetStaticType()->AddField(std::move(x));
      GetStaticType()->AddField(std::move(y));
      GetStaticType()->AddField(std::move(z));
      GetStaticType()->AddField(std::move(w));
    }
  }
}

class Cat
{
public:
  DeclareType(Cat)
  void Print()
  {
    std::cout << "Meow" << std::endl;
  }
};
DefineType(Cat)
{
  auto print = BindFunction<decltype(&Cat::Print), &Cat::Print>("Print");
  GetStaticType()->AddFunction(std::move(print));
}

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
  DocumentedObject::InitializeType();
  Type::InitializeType();
  Property::InitializeType();
  Function::InitializeType();
  Field::InitializeType();
  Test::Test2::Animal::InitializeType();
  Cat::InitializeType();

  char test = -2;

  auto char_Type = TypeId<char>();
  auto u8_Type = TypeId<u8>();
  //auto char_Type = TypeId<char>;
  auto i8_Type = TypeId<i8>();
  auto const_char = TypeId<const char>();


  auto animalType = Test::Test2::Animal::GetStaticType();
  auto catType = Cat::GetStaticType();


  Test::Test2::Animal animal;
  Cat cat;

  std::cout << "Return: " << animalType->GetFirstFunction("Print")->Invoke(&animal, 1).As<float>() << std::endl;
  auto doesThisWork2 = catType->GetFirstFunction("Print")->Invoke(&cat);

  auto property = animalType->GetFirstProperty("X");
  property->GetSetter()->Invoke(&animal, 5);
  auto i = property->GetGetter()->Invoke(&animal).As<int>();


  auto fielder = animalType->GetFirstField("Y");
  fielder->GetSetter()->Invoke(&animal, 12);
  auto j = fielder->GetGetter()->Invoke(&animal).As<int>();
}
