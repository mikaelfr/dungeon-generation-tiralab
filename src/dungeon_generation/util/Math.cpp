#include "Math.h"
#include "Random.h"
#define _USE_MATH_DEFINES
#include <cmath>

/*
Returns a random point in a circle of given radius

@param radius Radius of the circle
@return Vec2 specifying the random point
*/
Vec2 Math::GetRandomPointInCircle(int radius)
{
    float t = 2.0f * (float)M_PI * Random::GetRandomValue();
    float u = Random::GetRandomValue() + Random::GetRandomValue();
    float r = (u > 1) ? 2 - u : u;
    return Vec2(radius * r * cos(t), radius * r * sin(t));
}

/*
Returns the min value out of a and b

@param a First value to compare
@param b Second value to compare
@return Lower of a and b
*/
int Math::Min(int a, int b)
{
    return (a > b) ? b : a;
}

/*
Returns the max value out of a and b

@param a First value to compare
@param b Second value to compare
@return Higher of a and b
*/
int Math::Max(int a, int b)
{
    return (a > b) ? a : b;
}

/*
Returns the min value out of a and b

@param a First value to compare
@param b Second value to compare
@return Lower of a and b
*/
float Math::Min(float a, float b)
{
    return (a > b) ? b : a;
}

/*
Returns the max value out of a and b

@param a First value to compare
@param b Second value to compare
@return Higher of a and b
*/
float Math::Max(float a, float b)
{
    return (a > b) ? a : b;
}

/*
Returns the determinant of a,b,c,d

Optimized to really only work for quickly checking if the Delaunay condition holds for 
the circle comprised of counter clockwise a,b,c and point d

@param a Point of the triangle
@param b Point of the triangle
@param c Point of the triangle
@param d Point to test
@returns Determinant as a float
*/
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

/*
Returns true if points a, b and c are in clockwise order

@param a First point
@param b Second point
@param c Third point
@return True if a,b,c clockwise, false otherwise
*/
bool Math::IsClockwise(Vec2 a, Vec2 b, Vec2 c)
{
    return (b.x - a.x) * (b.y + a.y) + (c.x - b.x) * (c.y + b.y) + (a.x - c.x) * (a.y + c.y) > 0;
}
