#include <iostream>
#include "Type.hpp"

namespace YTE
{
  class XboxController
  {
  public:
    YTEDeclareType(XboxController);
  };

  YTEDefineType(XboxController)
  {
    YTERegisterType(XboxController);
  }

  enum class ControllerId : uint32_t
  {
    Xbox_P1,
    Xbox_P2,
    Xbox_P3,
    Xbox_P4,
    Xbox_Controllers_Number,
    Unknown
  };

  class GamepadSystem
  {
  public:
    YTEDeclareType(GamepadSystem);
    XboxController* GetXboxController(ControllerId aId)
    {
      return nullptr;
    }
  };

  YTEDefineType(GamepadSystem)
  {
    YTERegisterType(GamepadSystem);
    //auto size = CountFunctionArguments<decltype(&GamepadSystem::GetXboxController)>::template Size();

    //YTEBindFunction(&GamepadSystem::GetXboxController, YTENoOverload, "GetXboxController", YTEParameterNames("aController")).Description()
    //  = "Gets you the given controller. Warning: Controller may not be plugged in/active.";
  }
}

YTEDeclareExternalType(YTE::ControllerId);

YTEDefineExternalType(YTE::ControllerId)
{
  YTERegisterType(YTE::ControllerId);

  //  YTEBindEnumValue(ControllerId::Xbox_P1, "Xbox_P1");
  //  YTEBindEnumValue(ControllerId::Xbox_P2, "Xbox_P2");
  //  YTEBindEnumValue(ControllerId::Xbox_P3, "Xbox_P3");
  //  YTEBindEnumValue(ControllerId::Xbox_P4, "Xbox_P4");
  //  YTEBindEnumValue(ControllerId::Xbox_Controllers_Number, "Xbox_Controllers_Number");
  //  YTEBindEnumValue(ControllerId::Unknown, "Unknown");
}

int main()
{
  auto func = YTE::Binding<decltype(&YTE::GamepadSystem::GetXboxController)>:: template BindFunction<&YTE::GamepadSystem::GetXboxController>("GetXboxController");
}
