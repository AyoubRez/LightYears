#include "gameFramework/GameApplication.h"
#include "framework/World.h"

ly::Application* get_application()
{
    return new ly::GameApplication();
}

namespace ly
{
    GameApplication::GameApplication()
    {
        LoadWorld<World>();
    }
}
