#pragma once
#include "framework/Actor.h"


namespace ly
{
    class Spaceship : public Actor
    {
    public:
        Spaceship(World* owningWorld, const std::string& texturePath = "");
        void Tick(float delta_time) override;
        void BeginPlay() override;
        void SetVelocity(const sf::Vector2f& velocity);
        sf::Vector2f GetVelocity() const { return mVelocity; }

    private:
        sf::Vector2f mVelocity;
    };
}
