#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

struct Vec2
{
    Vec2()
    {
        x = 0.0f;
        y = 0.0f;
    }

    Vec2(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

    Vec2 Normalized() const
    {
        if (Length() == 0.0f)
            return Vec2(0.0f, 0.0f);

        return Vec2(x / Length(), y / Length());
    }

    float Length() const
    {
        return sqrtf(x * x + y * y);
    }

    inline bool operator==(const Vec2& other) const
    {
        return x == other.x && y == other.y;
    }

    inline Vec2 operator-() const
    {
        return Vec2(-x, -y);
    }

    inline Vec2& operator+=(const Vec2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    inline Vec2& operator-=(const Vec2& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    inline Vec2& operator*=(float value)
    {
        x *= value;
        y *= value;
        return *this;
    }

    inline Vec2& operator*=(int value)
    {
        x *= value;
        y *= value;
        return *this;
    }

    inline friend Vec2 operator+(Vec2 lhs, const Vec2& rhs)
    {
        lhs += rhs;
        return lhs;
    }

    inline friend Vec2 operator-(Vec2 lhs, const Vec2& rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    inline friend Vec2 operator*(Vec2 lhs, float value)
    {
        lhs *= value;
        return lhs;
    }

    inline friend Vec2 operator*(Vec2 lhs, int value)
    {
        lhs *= value;
        return lhs;
    }

    float x;
    float y;
};
