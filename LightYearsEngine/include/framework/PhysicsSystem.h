#pragma once

#include "Core.h"
#include "box2d/id.h"
#include "box2d/types.h"

namespace ly
{
    class Actor;

    class PhysicsSystem
    {
    public:
        static PhysicsSystem& Get();
        void Step(float delta_time);
        b2BodyId AddListener(Actor* listener) const;
        float GetPhysicsScale() const { return mPhysicsScale; }
        void RemoveListener(b2BodyId bodyToRemove);
        ~PhysicsSystem();

        void BeginContact(const b2ContactBeginTouchEvent& contact);
        void EndContact(const b2ContactEndTouchEvent& contact);
        void HitContact(const b2ContactHitEvent& contact);
        
        void CleanUp();

    protected:
        PhysicsSystem();

    private:
        static TUniquePtr<PhysicsSystem> m_physicsSystem;

        void ProcessContactEvents();
        void ProcessPendingRemoveListeners();
        b2WorldId mPhysicsWorldId = b2_nullWorldId;
        float mPhysicsScale = 0.01f;
        int SubStepCount = 4;

        TArray<b2BodyId> mPendingRemoveListener;
    };
}
