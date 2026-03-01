#pragma once

#include "Application.h"
#include "framework/Core.h"
#include "SFML/Graphics/RenderWindow.hpp"

namespace ly
{
    class Actor;
    class Application;

    class World
    {
    public:
        World(Application* owningApp);

        void BeginPlayInternal();
        void TickInternal(float delta_time);
        void Render(sf::RenderWindow& window);

        virtual ~World();

        template <typename ActorType, typename... Args>
        TWeakPtr<ActorType> SpawnActor(Args... args);

        sf::Vector2u GetWindowSize() const;
        void CleanCycle();

    private:
        void Tick(float delta_time);
        void BeginPlay();
        Application* m_OwningApp;
        bool m_BeganPlay;

        TArray<TSharedPtr<Actor>> m_Actors;
        TArray<TSharedPtr<Actor>> m_PendingActors;
    };

    template <typename ActorType, typename... Args>
    TWeakPtr<ActorType> World::SpawnActor(Args... args)
    {
        TSharedPtr<ActorType> newActor{new ActorType(this, args...)};
        m_PendingActors.push_back(newActor);
        return newActor;
    }
}
