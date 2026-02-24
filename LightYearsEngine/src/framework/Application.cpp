#include "framework/Core.h"
#include "framework/Application.h"
#include "framework/World.h"

namespace ly
{
    Application::Application(
        unsigned int windowWidth, unsigned int windowHeight, const std::string& windowTitle, std::uint32_t style)
        : m_Window({sf::VideoMode({windowWidth, windowHeight}), windowTitle, style}),
          m_TargetFrameRate(60.f),
          m_TickClock(),
          m_CurrentWorld(nullptr)
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

    void Application::TickInternal(float delta_time)
    {
        Tick(delta_time);
        if (m_CurrentWorld)
        {
            m_CurrentWorld->TickInternal(delta_time);
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
        sf::CircleShape shape(50.f);
        shape.setFillColor(sf::Color::Green);
        shape.setOrigin({50.f, 50.f});
        shape.setPosition({m_Window.getSize().x / 2.f, m_Window.getSize().y / 2.f});
        m_Window.draw(shape);
    }
}
