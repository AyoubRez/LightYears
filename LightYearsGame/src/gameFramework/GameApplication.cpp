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
        : Application{600, 980, "Light Years", sf::Style::Titlebar | sf::Style::Close}
    {
        TWeakPtr<World> newWorld = LoadWorld<World>();
        newWorld.lock()->SpawnActor<Actor>();
        actorToDestroy = newWorld.lock()->SpawnActor<Actor>();

        counter = 0;
    }

    void GameApplication::Tick(float delta_time)
    {
        counter += delta_time;
        if (counter > 2.f)
        {
            if (!actorToDestroy.expired())
            {
                actorToDestroy.lock()->Destroy();
            }
        }
    }
}
