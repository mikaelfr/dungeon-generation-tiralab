#include "Math.h"
#include "Random.h"
#define _USE_MATH_DEFINES
#include <cmath>

Vec2 Math::GetRandomPointInCircle(int radius)
{
    float t = 2.0f * (float)M_PI * Random::GetRandomValue();
    float u = Random::GetRandomValue() + Random::GetRandomValue();
    float r = (u > 1) ? 2 - u : u;
    return Vec2(radius * r * cos(t), radius * r * sin(t));
}

int Math::Min(int a, int b)
{
    return (a > b) ? b : a;
}

int Math::Max(int a, int b)
{
    return (a > b) ? a : b;
}

float Math::Min(float a, float b)
{
    return (a > b) ? b : a;
}

float Math::Max(float a, float b)
{
    return (a > b) ? a : b;
}

float Math::Determinant(Vec2 a, Vec2 b, Vec2 c, Vec2 d)
{
    return d.x * c.y * (b.x * b.x + b.y * b.y) - c.x * d.y * (b.x * b.x + b.y * b.y) -
           d.x * b.y * (c.x * c.x + c.y * c.y) + b.x * d.y * (c.x * c.x + c.y * c.y) +
           c.x * b.y * (d.x * d.x + d.y * d.y) - b.x * c.y * (d.x * d.x + d.y * d.y) -
           d.x * c.y * (a.x * a.x + a.y * a.y) + c.x * d.y * (a.x * a.x + a.y * a.y) +
           d.x * a.y * (c.x * c.x + c.y * c.y) - a.x * d.y * (c.x * c.x + c.y * c.y) -
           c.x * a.y * (d.x * d.x + d.y * d.y) + a.x * c.y * (d.x * d.x + d.y * d.y) +
           d.x * b.y * (a.x * a.x + a.y * a.y) - b.x * d.y * (a.x * a.x + a.y * a.y) -
           d.x * a.y * (b.x * b.x + b.y * b.y) + a.x * d.y * (b.x * b.x + b.y * b.y) +
           b.x * a.y * (d.x * d.x + d.y * d.y) - a.x * b.y * (d.x * d.x + d.y * d.y) -
           c.x * b.y * (a.x * a.x + a.y * a.y) + b.x * c.y * (a.x * a.x + a.y * a.y) +
           c.x * a.y * (b.x * b.x + b.y * b.y) - a.x * c.y * (b.x * b.x + b.y * b.y) -
           b.x * a.y * (c.x * c.x + c.y * c.y) + a.x * b.y * (c.x * c.x + c.y * c.y);
}

bool Math::IsClockwise(Vec2 a, Vec2 b, Vec2 c)
{
    return (b.x - a.x) * (b.y + a.y) + (c.x - b.x) * (c.y + b.y) + (a.x - c.x) * (a.y + c.y) > 0;
}
