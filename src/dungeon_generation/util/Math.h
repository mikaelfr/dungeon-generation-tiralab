#pragma once

#include "../data/Vector.h"

/*
Static class containing math utility functions
*/
class Math
{
public:
    static Vec2 GetRandomPointInCircle(int radius);

    static inline int Abs(int a) { return (a < 0) ? -a : a; }
    static inline float Abs(float a) { return (a < 0) ? -a : a; }
    static int Min(int a, int b);
    static int Max(int a, int b);
    static float Min(float a, float b);
    static float Max(float a, float b);

    // Determinant for Delaunauy triangulation
    // MILITARY USE ONLY, NOT FOR THE GENERAL PUBLIC
    static float Determinant(Vec2 a, Vec2 b, Vec2 c, Vec2 d);

    static bool IsClockwise(Vec2 a, Vec2 b, Vec2 c);

private:
    // Prevent creation of instances
    Math() {}
    ~Math() {}
};
