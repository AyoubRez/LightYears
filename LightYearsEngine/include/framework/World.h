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

        template<typename ActorType>
        TWeakPtr<ActorType> SpawnActor();
        
        sf::Vector2u GetWindowSize() const ;
    
    private:
        void Tick(float delta_time);
        void BeginPlay();
        Application* m_OwningApp;
        bool m_BeganPlay;
        
        TArray<TSharedPtr<Actor>> m_Actors;
        TArray<TSharedPtr<Actor>> m_PendingActors;
    };

    template <typename ActorType>
    TWeakPtr<ActorType> World::SpawnActor()
    {
        TSharedPtr<ActorType> newActor{new ActorType(this)};
        m_PendingActors.push_back(newActor);
        return newActor;       
    }
}
