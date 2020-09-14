#include "Room.h"

Room::Room()
{
    width = 0;
    height = 0;
    x = 0;
    y = 0;
}

Room::Room(int width, int height, int x, int y)
{
    this->width = width;
    this->height = height;
    this->x = x;
    this->y = y;
}

bool Room::IsColliding(const Room& other) const
{
    return Math::Abs(x - other.x) <= (width + other.width) * 0.5f && Math::Abs(y - other.y) <= (height + other.height) * 0.5f;
}

Vec2i Room::GetVectorBetween(const Room& other) const
{
    return Vec2i(other.x - x, other.y - y);
}

Vec2i Room::Move(const Vec2i& dir)
{
    x += dir.x;
    y += dir.y;

    return Vec2i(x, y);
}

Array<Vec2i> Room::GetVertices(int scale) const
{
    Array<Vec2i> arr(4);

    arr.Add(Vec2i((x - width / 2) * scale, (y - height / 2) * scale));
    arr.Add(Vec2i((x - width / 2) * scale, (y + height / 2) * scale));
    arr.Add(Vec2i((x + width / 2) * scale, (y + height / 2) * scale));
    arr.Add(Vec2i((x + width / 2) * scale, (y - height / 2) * scale));

    return arr;
}

bool Room::operator==(const Room& other) const
{
    return x == other.x && y == other.y && width == other.width && height == other.height;
}
