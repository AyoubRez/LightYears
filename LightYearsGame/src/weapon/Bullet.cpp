#include "weapon/Bullet.h"

namespace ly
{
    Bullet::Bullet(World* world, Actor* owner, const std::string& texturePath, float speed, float damage)
        : Actor(world, texturePath),
          mOwner(owner),
          mSpeed(speed),
          mDamage(damage)
    {
    }

    void Bullet::SetSpeed(float speed)
    {
        mSpeed = speed;
    }

    void Bullet::SetDamage(float damage)
    {
        mDamage = damage;
    }

    void Bullet::Tick(float delta_time)
    {
        Actor::Tick(delta_time);
        Move(delta_time);
        if (IsActorOuOfWindowBounds())
        {
            Destroy();
        }
    }

    void Bullet::Move(float delta_time)
    {
        AddActorLocationOffset(GetActorRightDirection() * mSpeed * delta_time * -1.f);
    }
}
