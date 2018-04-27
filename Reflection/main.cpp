#include <iostream>
#include "Type.hpp"

namespace YTE
{
  class XboxController;

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
    XboxController* GetXboxController(ControllerId aId);
  };
}

int main()
{
  auto func = YTE::Binding<decltype(&YTE::GamepadSystem::GetXboxController)>:: template BindFunction<&YTE::GamepadSystem::GetXboxController>("GetXboxController");
}
