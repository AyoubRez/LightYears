#pragma once

#include "framework/Actor.h"

namespace ly
{
    class Bullet : public Actor
    {
    public:
        Bullet(World* world, Actor* owner, const std::string& texturePath, float speed = 700.f, float damage = 10.f);

        void SetSpeed(float speed);
        void SetDamage(float damage);
        
        void Tick(float delta_time) override;
       

    private:
        void Move(float delta_time);
        Actor* mOwner;
        float mSpeed;
        float mDamage;
    };
}
