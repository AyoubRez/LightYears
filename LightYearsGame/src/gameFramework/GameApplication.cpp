#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include  "framework/Actor.h"
#include "framework/Core.h"
#include "config.h"
#include "framework/AssetManager.h"
#include "player/PlayerSpaceship.h"
#include "spaceship/Spaceship.h"

ly::Application* get_application()
{
    return new ly::GameApplication();
}

namespace ly
{
    GameApplication::GameApplication()
        : Application{600, 980, "Light Years", sf::Style::Titlebar | sf::Style::Close}
    {
        AssetManager::Get().SetAssetRootDirectory(GetResourceDir());
        TWeakPtr<World> newWorld = LoadWorld<World>();
        testPlayerSpaceship = newWorld.lock()->SpawnActor<PlayerSpaceship>();
        testPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));
        testPlayerSpaceship.lock()->SetActorRotation(sf::degrees(0.f));

        TWeakPtr<Spaceship> testSpaceShip =
            newWorld.lock()->SpawnActor<Spaceship>();
        testSpaceShip.lock()->SetTexture("SpaceShooterRedux/PNG/playerShip1_blue.png");
        testSpaceShip.lock()->SetActorLocation(sf::Vector2f(100.f, 50.f));

        counter = 0;
    }

    void GameApplication::Tick(float delta_time)
    {
        counter += delta_time;
        if (counter > 10.f)
        {
            if (!testPlayerSpaceship.expired())
            {
                testPlayerSpaceship.lock()->Destroy();
            }
        }
    }
}
