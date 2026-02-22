#include <iostream>

#include "framework/Application.h"

namespace ly
{
    Application::Application()
        : m_window({sf::VideoMode({1024, 1440}), "Light Years"}),
          m_target_frame_rate(30.f),
          m_tick_clock()
    {
    }

    void Application::Run()
    {
        m_tick_clock.restart();
        float elapsed_time = 0.f;
        float target_delta_time = 1.f / m_target_frame_rate;
        while (m_window.isOpen())
        {
            while (const std::optional event = m_window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                    m_window.close();
            }
            float frame_delta_time = m_tick_clock.restart().asSeconds();
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
    }

    void Application::Tick(float delta_time)
    {
    }

    void Application::RenderInternal()
    {
        m_window.clear();
        Render();
        m_window.display();
    }

    void Application::Render()
    {
        sf::CircleShape shape(50.f);
        shape.setFillColor(sf::Color::Green);
        shape.setOrigin({50.f, 50.f});
        shape.setPosition({m_window.getSize().x / 2.f, m_window.getSize().y / 2.f});
        m_window.draw(shape);
    }
}
