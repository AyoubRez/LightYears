#pragma once
#include "spaceship/Spaceship.h"

namespace ly
{
    class BulletShooter;
    class PlayerSpaceship : public Spaceship
    {
    public:
        PlayerSpaceship(World* owningWorld,
                        const std::string& texturePath = "SpaceShooterRedux/PNG/playerShip1_blue.png");

        void Tick(float delta_time) override;
        void SetSpeed(float speed) { mSpeed = speed; }
        float GetSpeed() { return mSpeed; }
        void Shoot() override;

    private:
        void HandleInput();
        void ConsumeInput(float delta_time);
        void NormalizeInput();
        void ClampInputOnEdge();
        sf::Vector2f mMoveInput;
        float mSpeed;
        TUniquePtr<BulletShooter> mShooter;
    };
}
