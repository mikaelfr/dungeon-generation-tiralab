#pragma once

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

	int width;
	int height;
	int x;
	int y;
};
