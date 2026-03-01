#pragma once
#include "Shooter.h"
#include "SFML/System/Clock.hpp"

namespace ly
{
    class BulletShooter : public Shooter
    {
    public:
        BulletShooter(Actor* owner, float cooldownDuration= 0.3f);
        bool IsOnCooldown() const override;

    private:
        void ShootImpl() override;
        sf::Clock mCooldownClock;
        float mCooldownDuration;
    };
}
