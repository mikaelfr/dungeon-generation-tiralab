#pragma once

#include "../util/Math.h"
#include "Array.h"

struct Room
{
    Room();
    Room(int width, int height, int x, int y);

    bool IsColliding(const Room& other) const;
    Vec2i GetVectorBetween(const Room& other) const;
    Vec2i Move(const Vec2i& dir);
    Array<Vec2i> GetVertices(int scale = 1) const;

    bool operator==(const Room& other) const;

    int width;
    int height;
    int x;
    int y;
};
