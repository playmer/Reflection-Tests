#include <iostream>
#include "Reflection.hpp"


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

template<typename Woo, typename Boy>
struct TemplatedThing
{

};

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
  std::cout << GetTypeName<UrKidStruct>().data() << std::endl;
  std::cout << GetTypeName<TemplatedThing<UrKidClass, UrKidStruct>>().data() << std::endl;


  constexpr ConstexprToken<64> copyTest{doesThisWork};
  std::cout << "Copying works: " << copyTest.data() << std::endl;

  constexpr auto func1 = GetFunctionSignature<decltype(Function::Func1)*, Function::Func1>();
  //constexpr auto func2 = GetFunctionSignature<decltype(Func2)*, Func2>();
  std::cout << func1.data() << std::endl;
  //printf("%s\n", func2.mData);
}