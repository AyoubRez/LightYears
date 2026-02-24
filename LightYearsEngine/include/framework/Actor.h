#pragma once

namespace ly
{
    class World;

    class Actor
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
