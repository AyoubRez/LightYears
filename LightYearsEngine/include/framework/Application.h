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
        Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& windowTitle,
                    std::uint32_t style);
        void Run();

        template <typename WorldType>
        TWeakPtr<WorldType> LoadWorld();
        sf::Vector2u GetWindowSize() const;

    private:
        void TickInternal(float delta_time);
        virtual void Tick(float delta_time);
        void RenderInternal();
        virtual void Render();
        sf::RenderWindow m_Window;
        float m_TargetFrameRate;
        sf::Clock m_TickClock;

        TSharedPtr<World> m_CurrentWorld;
        sf::Clock m_CleanCycleClock;
        float m_CleanCycleInterval;
    };

    template <typename WorldType>
    TWeakPtr<WorldType> Application::LoadWorld()
    {
        TSharedPtr<WorldType> newWorld{new WorldType(this)};
        m_CurrentWorld = newWorld;
        m_CurrentWorld->BeginPlayInternal();
        return newWorld;
    }
}
