#pragma once

#include "../util/Math.h"

struct Room
{
	Room()
	{
		width = 0;
		height = 0;
		x = 0;
		y = 0;
	}

	Room(int width, int height, int x, int y)
	{
		this->width = width;
		this->height = height;
		this->x = x;
		this->y = y;
	}

	bool IsColliding(const Room& other) const
	{
		return Math::Abs(x - other.x) <= (width + other.width) * 0.5f && Math::Abs(y - other.y) <= (height + other.height) * 0.5f;
	}

	Vec2i GetVectorBetween(const Room& other) const
	{
		return Vec2i(other.x - x, other.y - y);
	}

	void Move(const Vec2i& dir)
	{
		x += dir.x;
		y += dir.y;
	}

	int width;
	int height;
	int x;
	int y;
};
