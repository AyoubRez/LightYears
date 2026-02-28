#include "framework/Core.h"
#include "framework/Application.h"
#include "framework/AssetManager.h"
#include "framework/World.h"

namespace ly
{
    Application::Application(
        unsigned int windowWidth, unsigned int windowHeight, const std::string& windowTitle, std::uint32_t style)
        : m_Window({sf::VideoMode({windowWidth, windowHeight}), windowTitle, style}),
          m_TargetFrameRate(60.f),
          m_TickClock(),
          m_CurrentWorld(nullptr),
          m_CleanCycleClock(),
          m_CleanCycleInterval(10.f)
    {
    }

    void Application::Run()
    {
        m_TickClock.restart();
        float elapsed_time = 0.f;
        float target_delta_time = 1.f / m_TargetFrameRate;
        while (m_Window.isOpen())
        {
            while (const std::optional event = m_Window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                    m_Window.close();
            }
            float frame_delta_time = m_TickClock.restart().asSeconds();
            elapsed_time += frame_delta_time;
            while (elapsed_time > target_delta_time)
            {
                elapsed_time -= target_delta_time;
                TickInternal(target_delta_time);
                RenderInternal();
            }
        }
    }

    sf::Vector2u Application::GetWindowSize() const
    {
        return m_Window.getSize();
    }

    void Application::TickInternal(float delta_time)
    {
        Tick(delta_time);
        if (m_CurrentWorld)
        {
            m_CurrentWorld->TickInternal(delta_time);
        }
        if (m_CleanCycleClock.getElapsedTime().asSeconds() >= m_CleanCycleInterval)
        {
            m_CleanCycleClock.restart();
            AssetManager::Get().CleanCycle();
        }
    }

    void Application::Tick(float delta_time)
    {
    }

    void Application::RenderInternal()
    {
        m_Window.clear();
        Render();
        m_Window.display();
    }

    void Application::Render()
    {
        if (m_CurrentWorld)
        {
            m_CurrentWorld->Render(m_Window);
        }
    }
}
