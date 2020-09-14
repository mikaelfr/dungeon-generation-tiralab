#pragma once

#include "../data/Vector.h"

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

private:
    // Prevent creation of instances
    Math() {}
    ~Math() {}
};
