#pragma once

#include "../util/Math.h"
#include "Array.h"

struct Room
{
    Room();
    Room(float width, float height, float x, float y);

    bool IsColliding(const Room& other) const;
    Vec2 GetVectorBetween(const Room& other) const;
    Vec2 Move(const Vec2& dir);
    Array<Vec2> GetVertices(float scale = 1.0f) const;
    float DistanceToOrigin() const;

    static void FormTriangle(const std::shared_ptr<Room>& a, const std::shared_ptr<Room>& b, const std::shared_ptr<Room>& c);

    bool operator==(const Room& other) const;

    float width;
    float height;
    float x;
    float y;
    bool bMainRoom;

    Array<std::shared_ptr<Room>> connections;
};
