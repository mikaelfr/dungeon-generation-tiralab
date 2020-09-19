#include "Room.h"

Room::Room()
{
    width = 0;
    height = 0;
    x = 0;
    y = 0;
    bMainRoom = false;
}

Room::Room(float width, float height, float x, float y)
{
    this->width = width;
    this->height = height;
    this->x = x;
    this->y = y;
    this->bMainRoom = false;
}

bool Room::IsColliding(const Room& other) const
{
    return Math::Abs(x - other.x) <= (width + other.width) * 0.5f && Math::Abs(y - other.y) <= (height + other.height) * 0.5f;
}

Vec2 Room::GetVectorBetween(const Room& other) const
{
    return Vec2(other.x - x, other.y - y);
}

Vec2 Room::Move(const Vec2& dir)
{
    x += dir.x;
    y += dir.y;

    return Vec2(x, y);
}

Array<Vec2> Room::GetVertices(float scale) const
{
    Array<Vec2> arr(4);

    arr.Add(Vec2((x - width / 2) * scale, (y - height / 2) * scale));
    arr.Add(Vec2((x - width / 2) * scale, (y + height / 2) * scale));
    arr.Add(Vec2((x + width / 2) * scale, (y + height / 2) * scale));
    arr.Add(Vec2((x + width / 2) * scale, (y - height / 2) * scale));

    return arr;
}

// Distance to origin aka position length
float Room::DistanceToOrigin() const
{
    return Vec2(x, y).Length();
}

void Room::FormTriangle(const std::shared_ptr<Room>& a, const std::shared_ptr<Room>& b, const std::shared_ptr<Room>& c)
{
    a->connections.Add(b, c);
    b->connections.Add(a, c);
    c->connections.Add(a, b);
}

bool Room::operator==(const Room& other) const
{
    return x == other.x && y == other.y && width == other.width && height == other.height;
}
