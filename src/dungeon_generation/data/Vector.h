#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

struct Vec2i
{
    Vec2i()
    {
        x = 0;
        y = 0;
    }

    Vec2i(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    Vec2i Normalized() const
    {
        if (Length() == 0.0f)
            return Vec2i(0, 0);

        return Vec2i((int)(x / Length()), (int)(y / Length()));
    }

    float Length() const
    {
        return sqrtf((float)(x * x + y * y));
    }

    inline bool operator==(const Vec2i& other) const
    {
        return x == other.x && y == other.y;
    }

    int x;
    int y;
};
