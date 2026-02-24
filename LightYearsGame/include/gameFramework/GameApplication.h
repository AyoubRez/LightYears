#pragma once

#include <framework/Actor.h>
#include <framework/Application.h>
#include <framework/Core.h>

namespace ly
{
    class Actor;
    class GameApplication : public Application
    {
        public:
        GameApplication();
        void Tick(float delta_time) override;
        
    private:
        float counter = 0;
        TWeakPtr<Actor> actorToDestroy;
    };
}
