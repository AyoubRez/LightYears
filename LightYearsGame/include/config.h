#pragma once

#include <string>


std::string GetResourceDir()
{
#ifdef NDEBUG // release
    return "assets/";
#else
    return "C:/Users/AyoubREZZOUK/Desktop/GameDev/game/LightYears/LightYearsGame/assets/";
#endif
}
 
