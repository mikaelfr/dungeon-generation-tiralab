#pragma once

#include "../util/Math.h"
#include "Array.h"
#include "Set.h"
#include "DisjointSet.h"
#include "Tuple.h"

struct Room
{
    enum RoomType
    {
        UNKNOWN = 0,
        NORMAL,
        MAIN,
        HALLWAY
    };

    Room();
    Room(float width, float height, float x, float y);

    bool IsColliding(const Room& other) const;
    bool IsColliding(const Tuple<Vec2, Vec2>& other) const;
    Vec2 GetVectorBetween(const Room& other) const;
    Vec2 Move(const Vec2& dir);
    Array<Vec2> GetVertices(float scale = 1.0f) const;
    float DistanceToOrigin() const;
    bool CloseEnoughX(const Room& other);
    bool CloseEnoughY(const Room& other);

    /*
    Returns the position of this room as a two-dimensional vector

    @return Position of this room as a Vec2
    */
    inline Vec2 GetPos() const
    {
        return Vec2(x, y);
    }

    bool operator==(const Room& other) const;

    /*
    Implicit conversion of Room to Vec2.
    This is defined to be the position of the room.

    @return Position of this room as a Vec2
    */
    inline operator Vec2() const
    {
        return GetPos();
    }

    friend std::ostream& operator<<(std::ostream& os, const Room& room);

    float width;
    float height;
    float x;
    float y;
    RoomType eRoomType;
    bool bPartOfMST;
    Set<std::shared_ptr<Room>> neighbors;
    DisjointSet<Room*> set;
};
