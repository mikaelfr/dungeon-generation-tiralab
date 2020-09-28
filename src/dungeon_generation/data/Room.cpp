#include "Room.h"

Room::Room()
{
    width = 0;
    height = 0;
    x = 0;
    y = 0;
    this->eRoomType = UNKNOWN;
    this->set = DisjointSet<Room*>(this);
}

Room::Room(float width, float height, float x, float y)
{
    this->width = width;
    this->height = height;
    this->x = x;
    this->y = y;
    this->eRoomType = NORMAL;
    this->set = DisjointSet<Room*>(this);
}

bool Room::IsColliding(const Room& other) const
{
    return Math::Abs(x - other.x) <= (width + other.width) * 0.5f && Math::Abs(y - other.y) <= (height + other.height) * 0.5f;
}

bool Room::IsColliding(const Tuple<Vec2, Vec2>& other) const
{
    // We can assume that lines are always either horizontal or vertical
    float maxX = Math::Max(other.key.x, other.value.x);
    float minX = Math::Min(other.key.x, other.value.x);
    float maxY = Math::Max(other.key.y, other.value.y);
    float minY = Math::Min(other.key.y, other.value.y);
    if (x < maxX + width && x > minX - width && Math::Abs(y - other.key.y) < height)
    {
        return true;
    }
    else if (y < maxY + height && y > minY - height && Math::Abs(x - other.key.x) < width)
    {
        return true;
    }

    return false;
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

bool Room::CloseEnoughX(const Room& other)
{
    const float threshold = 5.0f;
    if (x > other.x)
    {
        return (x - width) - (other.x - width) > threshold;
    }
    else
    {
        return (other.x - width) - (x - width) > threshold;
    }
}

bool Room::CloseEnoughY(const Room& other)
{
    const float threshold = 5.0f;
    if (y > other.y)
    {
        return (y - height) - (other.y - height) > threshold;
    }
    else
    {
        return (other.y - height) - (y - height) > threshold;
    }
}

bool Room::operator==(const Room& other) const
{
    return x == other.x && y == other.y && width == other.width && height == other.height;
}
