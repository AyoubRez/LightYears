#pragma once

namespace ly
{
    class Application;

    class World
    {
    public:
        World(Application* owningApp);
        
        void BeginPlayInternal();
        void TickInternal(float delta_time);
        
        virtual ~World();

    private:
        void Tick(float delta_time);
        void BeginPlay();
        Application* m_OwningApp;
        bool m_BeganPlay;
    };
}
