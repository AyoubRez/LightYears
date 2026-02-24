#include "framework/Actor.h"
#include "framework/Core.h"

namespace ly
{
    Actor::Actor(World* owning_world)
        : m_OwningWorld(owning_world),
          m_BeganPlay(false)
    {
    }

    Actor::~Actor()
    {
    }

    void Actor::BeginPlayInternal()
    {
        if (!m_BeganPlay)
        {
            m_BeganPlay = true;
            BeginPlay();
        }
    }

    void Actor::BeginPlay()
    {
        LY_LOG("Actor began play");
    }

    void Actor::Tick(float delta_time)
    {
        LY_LOG("Actor ticked");
    }
}
