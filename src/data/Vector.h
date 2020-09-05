#pragma once

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

	int x;
	int y;
};
