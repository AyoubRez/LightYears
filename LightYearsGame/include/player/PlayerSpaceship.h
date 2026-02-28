#pragma once
#include "spaceship/Spaceship.h"

namespace ly
{
    class PlayerSpaceship : public Spaceship
    {
    public:
        PlayerSpaceship(World* owningWorld,
                        const std::string& texturePath = "SpaceShooterRedux/PNG/playerShip1_blue.png");

        void Tick(float delta_time) override;
        void SetSpeed(float speed) { mSpeed = speed; }
        float GetSpeed() { return mSpeed; }

    private:
        void HandleInput();
        void ConsumeInput(float delta_time);
        void NormalizeInput();
        void ClampInputOnEdge();
        sf::Vector2f mMoveInput;
        float mSpeed;
    };
}
