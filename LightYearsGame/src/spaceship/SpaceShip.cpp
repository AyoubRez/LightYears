#include "spaceship/Spaceship.h"

namespace ly
{
    Spaceship::Spaceship(World* owningWorld, const std::string& texturePath)
        : Actor{owningWorld, texturePath},
          mVelocity{}
    {
    }

    void Spaceship::Tick(float delta_time)
    {
        Actor::Tick(delta_time);
        AddActorLocationOffset(GetVelocity() * delta_time);
    }

    void Spaceship::BeginPlay()
    {
        Actor::BeginPlay();
        SetEnablePhysics(true);
    }

    void Spaceship::SetVelocity(const sf::Vector2f& velocity)
    {
        mVelocity = velocity;
    }

    void Spaceship::Shoot()
    {
    }
}
