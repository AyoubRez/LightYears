#pragma once

#include "framework/Object.h"

namespace ly
{
    class World;

    class Actor : public Object
    {
    public:
        Actor(World* owning_world);
        virtual ~Actor();
        void BeginPlayInternal();
        virtual void BeginPlay();
        virtual void Tick(float delta_time);

    private:
        World* m_OwningWorld;
        bool m_BeganPlay;
    };
}
