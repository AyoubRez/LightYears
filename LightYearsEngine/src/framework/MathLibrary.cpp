#include "framework/MathLibrary.h"
#include <cmath>

namespace ly
{
    const float PI = 3.1415926535f;

    sf::Vector2f RotationToVector(float rotation)
    {
        float radians = DegreesToRadians(rotation);
        return sf::Vector2f(cos(radians), sin(radians));
    }

    float DegreesToRadians(float degrees)
    {
        return degrees * PI / 180.f;
    }

    float RadiansToDegrees(float radians)
    {
        return radians * (180.f / PI);
    }
    
}