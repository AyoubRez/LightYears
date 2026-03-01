#include "weapon/BulletShooter.h"

#include "framework/Core.h"
#include "framework/World.h"
#include "SFML/System/Time.hpp"
#include "weapon/Bullet.h"


namespace ly
{
    BulletShooter::BulletShooter(Actor* owner, float cooldownDuration)
        : Shooter(owner),
          mCooldownClock(),
          mCooldownDuration(cooldownDuration)
    {
    }

    bool BulletShooter::IsOnCooldown() const
    {
        if (mCooldownClock.getElapsedTime().asSeconds() >= mCooldownDuration) return false;
        return true;
    }

    void BulletShooter::ShootImpl()
    {
        mCooldownClock.restart();
        TWeakPtr<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActor<Bullet>(
            GetOwner(), "SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
        newBullet.lock()->SetActorLocation(GetOwner()->GetActorLocation());
        newBullet.lock()->SetActorRotation(GetOwner()->GetActorRotation());
    }
}
