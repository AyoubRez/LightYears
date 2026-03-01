#include "framework/World.h"
#include "framework/Actor.h"
#include "framework/Core.h"


namespace ly
{
    World::World(Application* owningApp)
        : m_OwningApp(owningApp),
          m_BeganPlay(false),
          m_Actors{},
          m_PendingActors{}
    {
    }

    void World::BeginPlayInternal()
    {
        if (!m_BeganPlay)
        {
            m_BeganPlay = true;
            BeginPlay();
        }
    }

    void World::TickInternal(float delta_time)
    {
        for (TSharedPtr<Actor>& actor : m_PendingActors)
        {
            m_Actors.push_back(actor);
            actor->BeginPlayInternal();
        }
        m_PendingActors.clear();

        for (auto iter = m_Actors.begin(); iter != m_Actors.end();)
        {
            iter->get()->TickInternal(delta_time);
            ++iter;
        }
        Tick(delta_time);
    }

    World::~World()
    {
    }

    void World::Render(sf::RenderWindow& window)
    {
        for (auto& actor : m_Actors)
        {
            actor->Render(window);
        }
    }

    sf::Vector2u World::GetWindowSize() const
    {
        return m_OwningApp->GetWindowSize();
    }

    void World::CleanCycle()
    {
        LY_LOG("CleanCycle started");
        for (auto iter = m_Actors.begin(); iter != m_Actors.end();)
        {
            if (iter->get()->IsPendingDestroy())
            {
                iter = m_Actors.erase(iter);
            }else
            {
                ++iter;
            }
        }
        LY_LOG("CleanCycle completed");
    }

    void World::Tick(float delta_time)
    {
    }

    void World::BeginPlay()
    {
    }
}
