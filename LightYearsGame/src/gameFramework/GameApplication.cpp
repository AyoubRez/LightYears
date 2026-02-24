#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include  "framework/Actor.h"   
#include "framework/Core.h"

ly::Application* get_application()
{
    return new ly::GameApplication();
}

namespace ly
{
    GameApplication::GameApplication()
    {
        TWeakPtr<World> newWorld = LoadWorld<World>();
        newWorld.lock()->SpawnActor<Actor>();
        newWorld.lock()->SpawnActor<Actor>();
        newWorld.lock()->SpawnActor<Actor>();
        newWorld.lock()->SpawnActor<Actor>();
        newWorld.lock()->SpawnActor<Actor>();
        newWorld.lock()->SpawnActor<Actor>();
    }
}
