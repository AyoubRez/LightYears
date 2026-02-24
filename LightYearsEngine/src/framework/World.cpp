#include "framework/World.h"

#include "framework/Core.h"


namespace ly
{
    World::World(Application* owningApp)
        : m_OwningApp(owningApp),
          m_BeganPlay(false)
    {
    }

    void World::BeginPlayInternal()
    {
        if (!m_BeganPlay)
        {
            m_BeganPlay = true;
            BeginPlay();
        }
    }

    void World::TickInternal(float delta_time)
    {
        Tick(delta_time);
    }

    World::~World()
    {
    }

    void World::Tick(float delta_time)
    {
        LY_LOG("Tick at frame rate %f", 1.f / delta_time);
    }

    void World::BeginPlay()
    {
        LY_LOG("World began play");
    }
}
