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
    RegisterType<XboxController>();
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
    RegisterType<GamepadSystem>();

    //YTEBindProperty(&GamepadSystem::Get, &GamepadSystem::Set, "asd");
  }
}

YTEDeclareExternalType(YTE::ControllerId);

YTEDefineExternalType(YTE::ControllerId)
{
  RegisterType<YTE::ControllerId>();

  TypeBuilder<YTE::ControllerId> builder;

  //builder.Enum<YTE::ControllerId::Xbox_P1>("Xbox_P1");
}


int main()
{
}
