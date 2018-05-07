#include <iostream>
#include "Meta.hpp"

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


  static XboxController* STATIC_GetXboxController(ControllerId aId)
  {
    return nullptr;
  }

  class GamepadSystem
  {
  public:
    YTEDeclareType(GamepadSystem);
    XboxController* GetXboxControllerConst(ControllerId aId) const
    {
      return nullptr;
    }

    XboxController* GetXboxController(ControllerId aId)
    {
      return nullptr;
    }

    void Set(ControllerId) {};
    ControllerId Get() { return ControllerId::Xbox_P1; };
  };

  YTEDefineType(GamepadSystem)
  {
    YTERegisterType(GamepadSystem);

    YTEBindProperty(&GamepadSystem::Get, &GamepadSystem::Set, "asd");
  }
}

YTEDeclareExternalType(YTE::ControllerId);

YTEDefineExternalType(YTE::ControllerId)
{
  YTERegisterType(YTE::ControllerId);
}

int main()
{
  // These will all ICE.
  auto caller1 = YTE::Binding<decltype(&YTE::STATIC_GetXboxController)>::template Caller<&YTE::STATIC_GetXboxController>;
  //auto caller2 = YTE::Binding<decltype(&YTE::GamepadSystem::GetXboxControllerConst)>::template Caller<&YTE::GamepadSystem::GetXboxControllerConst>;
  //auto caller3 = YTE::Binding<decltype(&YTE::GamepadSystem::GetXboxController)>::template Caller<&YTE::GamepadSystem::GetXboxController>;
}
