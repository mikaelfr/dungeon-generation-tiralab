#include "Math.h"
#include "Random.h"
#define _USE_MATH_DEFINES
#include <cmath>

Vec2i Math::GetRandomPointInCircle(int radius)
{
    float t = 2.0f * (float)M_PI * Random::GetRandomValue();
    float u = Random::GetRandomValue() + Random::GetRandomValue();
    float r = (u > 1) ? 2 - u : u;
    return Vec2i((int)(radius * r * cos(t)), (int)(radius * r * sin(t)));
}

inline int Math::Min(int a, int b)
{
    return (a > b) ? b : a;
}

inline int Math::Max(int a, int b)
{
    return (a > b) ? a : b;
}

inline float Math::Min(float a, float b)
{
    return (a > b) ? b : a;
}

inline float Math::Max(float a, float b)
{
    return (a > b) ? a : b;
}
