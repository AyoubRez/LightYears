#pragma once

#include "framework/Core.h"

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
        
        virtual ~World();

        template<typename ActorType>
        TWeakPtr<ActorType> SpawnActor();
    
    private:
        void Tick(float delta_time);
        void BeginPlay();
        Application* m_OwningApp;
        bool m_BeganPlay;
        
        TArray<TSharedPtr<Actor>> m_actors;
        TArray<TSharedPtr<Actor>> m_pending_actors;
    };

    template <typename ActorType>
    TWeakPtr<ActorType> World::SpawnActor()
    {
        TSharedPtr<ActorType> newActor{new ActorType(this)};
        m_pending_actors.push_back(newActor);
        return newActor;       
    }
}
