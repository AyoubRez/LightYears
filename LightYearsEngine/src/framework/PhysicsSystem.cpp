#include "framework/PhysicsSystem.h"

#include "../../../build/_deps/box2d-src/src/body.h"
#include "box2d/box2d.h"
#include "framework/Actor.h"


namespace ly
{
    TUniquePtr<PhysicsSystem> PhysicsSystem::m_physicsSystem(nullptr);

    void PhysicsSystem::ProcessContactEvents()
    {
        if (!b2World_IsValid(mPhysicsWorldId))
            return;

        const b2ContactEvents events = b2World_GetContactEvents(mPhysicsWorldId);

        for (int i = 0; i < events.beginCount; ++i)
        {
            const b2ContactBeginTouchEvent& e = events.beginEvents[i];
            BeginContact(e);
        }

        for (int i = 0; i < events.endCount; ++i)
        {
            const b2ContactEndTouchEvent& e = events.endEvents[i];
            EndContact(e);
        }

        for (int i = 0; i < events.hitCount; ++i)
        {
            const b2ContactHitEvent& e = events.hitEvents[i];
            HitContact(e);
        }
    }

    void PhysicsSystem::ProcessPendingRemoveListeners()
    {
        if (!b2World_IsValid(mPhysicsWorldId))
        {
            mPendingRemoveListener.clear();
            return;
        }

        for (const b2BodyId bodyId : mPendingRemoveListener)
        {
            if (b2Body_IsValid(bodyId))
            {
                b2DestroyBody(bodyId);
            }
        }

        mPendingRemoveListener.clear();
    }

    PhysicsSystem& PhysicsSystem::Get()
    {
        if (!m_physicsSystem)
        {
            m_physicsSystem = std::move(TUniquePtr<PhysicsSystem>(new PhysicsSystem()));
        }
        return *m_physicsSystem;
    }

    void PhysicsSystem::Step(float delta_time)
    {
        if (!b2World_IsValid(mPhysicsWorldId))
            return;
        ProcessPendingRemoveListeners();
        b2World_Step(mPhysicsWorldId, delta_time, SubStepCount);
        ProcessContactEvents();
    }

    b2BodyId PhysicsSystem::AddListener(Actor* listener) const
    {
        if (!b2World_IsValid(mPhysicsWorldId)
            || listener == nullptr
            || listener->IsPendingDestroy())
        {
            return b2_nullBodyId;
        }
        b2BodyDef bodyDef = b2DefaultBodyDef();
        bodyDef.type = b2_dynamicBody;
        bodyDef.position = b2Vec2{
            listener->GetActorLocation().x * GetPhysicsScale(),
            listener->GetActorLocation().y * GetPhysicsScale()
        };
        bodyDef.enableSleep = false;
        bodyDef.rotation = b2MakeRot(listener->GetActorRotation().asRadians());
        bodyDef.userData = listener;

        b2BodyId bodyId = b2CreateBody(mPhysicsWorldId, &bodyDef);
        auto bound = listener->GetActorGlobalBounds();
        b2Polygon box = b2MakeBox(
            bound.size.x / 2.f * GetPhysicsScale()
            , bound.size.y / 2.f * GetPhysicsScale()
        );

        b2ShapeDef shapeDef = b2DefaultShapeDef();
        shapeDef.density = 1.0f;
        shapeDef.material.friction = 0.3f;
        shapeDef.isSensor = false;
        shapeDef.enableContactEvents = true;

        b2CreatePolygonShape(bodyId, &shapeDef, &box);
        return bodyId;
    }

    void PhysicsSystem::RemoveListener(b2BodyId bodyToRemove)
    {
        mPendingRemoveListener.push_back(bodyToRemove);
    }

    PhysicsSystem::PhysicsSystem()
    {
        b2WorldDef worldDef = b2DefaultWorldDef();
        worldDef.gravity = b2Vec2{0.f, 0.f};
        mPhysicsWorldId = b2CreateWorld(&worldDef);
    }

    PhysicsSystem::~PhysicsSystem()
    {
        if (b2World_IsValid(mPhysicsWorldId))
        {
            b2DestroyWorld(mPhysicsWorldId);
            mPhysicsWorldId = b2_nullWorldId;
        }
    }

    void PhysicsSystem::BeginContact(const b2ContactBeginTouchEvent& contact)
    {
        if (!b2Shape_IsValid(contact.shapeIdA) || !b2Shape_IsValid(contact.shapeIdB))
            return;

        const b2BodyId bodyA = b2Shape_GetBody(contact.shapeIdA);
        const b2BodyId bodyB = b2Shape_GetBody(contact.shapeIdB);

        Actor* actorA = b2Body_IsValid(bodyA) ? static_cast<Actor*>(b2Body_GetUserData(bodyA)) : nullptr;
        Actor* actorB = b2Body_IsValid(bodyB) ? static_cast<Actor*>(b2Body_GetUserData(bodyB)) : nullptr;

        if (actorA != nullptr && !actorA->IsPendingDestroy())
        {
            actorA->OnActorBeginOverlap(actorB);
        }

        if (actorB != nullptr && !actorB->IsPendingDestroy())
        {
            actorB->OnActorBeginOverlap(actorA);
        }
    }

    void PhysicsSystem::EndContact(const b2ContactEndTouchEvent& contact)
    {
        b2BodyId bodyA = b2_nullBodyId;
        b2BodyId bodyB = b2_nullBodyId;
        if (b2Shape_IsValid(contact.shapeIdA))
        {
            bodyA = b2Shape_GetBody(contact.shapeIdA);
        }

        if (b2Shape_IsValid(contact.shapeIdB))
        {
            bodyB = b2Shape_GetBody(contact.shapeIdB);
        }
        Actor* actorA = b2Body_IsValid(bodyA) ? static_cast<Actor*>(b2Body_GetUserData(bodyA)) : nullptr;
        Actor* actorB = b2Body_IsValid(bodyB) ? static_cast<Actor*>(b2Body_GetUserData(bodyB)) : nullptr;

        if (actorA != nullptr && !actorA->IsPendingDestroy())
        {
            actorA->OnActorEndOverlap(actorB);
        }

        if (actorB != nullptr && !actorB->IsPendingDestroy())
        {
            actorB->OnActorEndOverlap(actorA);
        }
    }

    void PhysicsSystem::HitContact(const b2ContactHitEvent& contact)
    {
        LY_LOG("HitContact");
    }

    void PhysicsSystem::CleanUp()
    {
        m_physicsSystem = std::move(TUniquePtr<PhysicsSystem>(new PhysicsSystem()));
    }
}
