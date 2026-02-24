#pragma once
#include <SFML/Graphics.hpp>
#include "World.h"
#include "framework/Core.h"

namespace ly
{
    class World;

    class Application
    {
    public:
        Application();
        void Run();

        template <typename WorldType>
        TWeakPtr<WorldType> LoadWorld();

    private:
        void TickInternal(float delta_time);
        virtual void Tick(float delta_time);
        void RenderInternal();
        virtual void Render();
        sf::RenderWindow m_window;
        float m_target_frame_rate;
        sf::Clock m_tick_clock;

        TSharedPtr<World> currentWorld;
    };

    template <typename WorldType>
    TWeakPtr<WorldType> Application::LoadWorld()
    {
        TSharedPtr<WorldType> newWorld{new WorldType(this)};
        currentWorld = newWorld;
        currentWorld->BeginPlayInternal();
        return newWorld;
    }
}
