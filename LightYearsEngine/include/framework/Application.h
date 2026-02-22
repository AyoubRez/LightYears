#pragma once
#include <SFML/Graphics.hpp>

namespace ly
{
    class Application
    {
    public:
        Application();
        
        void Run();

    private:
        void TickInternal(float delta_time);
        virtual void Tick(float delta_time);
        void RenderInternal();
        virtual void Render();
        sf::RenderWindow m_window;
        float  m_target_frame_rate;
        sf::Clock m_tick_clock;
    };
}
