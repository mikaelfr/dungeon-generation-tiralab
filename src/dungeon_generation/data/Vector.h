#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

/*
Simple two-dimensional floating point vector
*/
struct Vec2
{
    /*
    Default constructor producing a zero vector
    */
    Vec2()
    {
        x = 0.0f;
        y = 0.0f;
    }

    /*
    Constructor producing a vector (x, y)

    @param x Float x value for vector
    @param y Float y value for vector
    */
    Vec2(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

    /*
    Returns this vector normalized as a copy

    @return Normalized version of this vector as a new vector
    */
    Vec2 Normalized() const
    {
        if (Length() == 0.0f)
            return Vec2(0.0f, 0.0f);

        return Vec2(x / Length(), y / Length());
    }

    /*
    Returns the length of this vector

    @return Length of this vector
    */
    float Length() const
    {
        return sqrtf(x * x + y * y);
    }

    /*
    Overloaded equals operator, checks that x and y are exactly the same

    @param other Const reference to other vector to compare to
    @return True if equal, false otherwise
    */
    inline bool operator==(const Vec2& other) const
    {
        return x == other.x && y == other.y;
    }

    /*
    Negates this vector and returns a copy

    @return Return a copy of this vector negated
    */
    inline Vec2 operator-() const
    {
        return Vec2(-x, -y);
    }

    /*
    Overload for += operator for vectors
    Adds the other vector to this and returns a reference to this

    @param other Const reference to vector added to this
    @return Reference to this
    */
    inline Vec2& operator+=(const Vec2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    /*
    Overload for -= operator for vectors
    Subtracts the other vector from this and returns a reference to this

    @param other Const reference to vector substracted from this
    @return Reference to this
    */
    inline Vec2& operator-=(const Vec2& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    /*
    Overload for *= operator for floats
    Multiplies this vector by value and returns a reference to this

    @param value Value to multiply vector by
    @return Reference to this
    */
    inline Vec2& operator*=(float value)
    {
        x *= value;
        y *= value;
        return *this;
    }

    /*
    Overload for *= operator for ints
    Multiplies this vector by value and returns a reference to this

    @param value Value to multiply vector by
    @return Reference to this
    */
    inline Vec2& operator*=(int value)
    {
        x *= value;
        y *= value;
        return *this;
    }

    /*
    Overload for addition operator
    Adds lhs and rhs together and returns lhs

    @param lhs Left hand vector
    @param rhs Right hand vector
    @return lhs + rhs
    */
    inline friend Vec2 operator+(Vec2 lhs, const Vec2& rhs)
    {
        lhs += rhs;
        return lhs;
    }

    /*
    Overload for substraction operator
    Substracts rhs from lhs and returns lhs

    @param lhs Left hand vector
    @param rhs Right hand vector
    @return lhs - rhs
    */
    inline friend Vec2 operator-(Vec2 lhs, const Vec2& rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    /*
    Overload for multiplication operator
    Multiplies lhs by float value

    @param lhs Left hand vector
    @param value Float value
    @return lhs vector multiplied by value
    */
    inline friend Vec2 operator*(Vec2 lhs, float value)
    {
        lhs *= value;
        return lhs;
    }

    /*
    Overload for multiplication operator
    Multiplies lhs by int value

    @param lhs Left hand vector
    @param value Int value
    @return lhs vector multiplied by value
    */
    inline friend Vec2 operator*(Vec2 lhs, int value)
    {
        lhs *= value;
        return lhs;
    }

    /*
    Overload for stream operator
    Inserts the string representation of this object into the stream

    @param os Reference to the stream
    @param vec Const reference to the streamed vector
    @return os
    */
    inline friend std::ostream& operator<<(std::ostream& os, const Vec2& vec)
    {
        os << '{' << "\"x\": " << vec.x << ", \"y\": " << vec.y << '}';
        return os;
    }

    float x;
    float y;
};
