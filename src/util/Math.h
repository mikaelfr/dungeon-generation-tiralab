#pragma once

#include "../data/Vector.h"

class Math
{
public:
	static Vec2i GetRandomPointInCircle(int radius);

	static int Min(int a, int b);
	static int Max(int a, int b);
	static float Min(float a, float b);
	static float Max(float a, float b);

private:
	// Prevent creation of instances
	Math();
	~Math();
};
