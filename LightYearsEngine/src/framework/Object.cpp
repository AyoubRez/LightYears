#include "framework/Object.h"
#include "framework/Core.h"


namespace ly
{
    Object::Object()
        : m_IsPendingDestroy(false)
    {
    }

    Object::~Object()
    {
        LY_LOG("Object destroyed");
    }

    void Object::Destroy()
    {
        m_IsPendingDestroy = true;
    }
}
