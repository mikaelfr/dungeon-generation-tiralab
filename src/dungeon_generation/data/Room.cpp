#include "Room.h"

/*
Default constructor of Room
*/
Room::Room()
{
    width = 0;
    height = 0;
    x = 0;
    y = 0;
    eRoomType = UNKNOWN;
    bPartOfMST = false;
    set = DisjointSet<Room*>(this);
}

/*
Constructor for Room with width, height, x and y

@param width Width of the room
@param height Height of the room
@param x X position of the room
@param y Y position of the room
*/
Room::Room(float width, float height, float x, float y)
{
    this->width = width;
    this->height = height;
    this->x = x;
    this->y = y;
    this->eRoomType = NORMAL;
    this->bPartOfMST = false;
    this->set = DisjointSet<Room*>(this);
}

/*
Checks if this room is colliding with the specified room.

@param other Const reference to another room
@return True if the rooms are overlapping
*/
bool Room::IsColliding(const Room& other) const
{
    return Math::Abs(x - other.x) <= (width + other.width) * 0.5f && Math::Abs(y - other.y) <= (height + other.height) * 0.5f;
}

/*
Checks if this room is colliding with an axis aligned line.

@param other A const reference to a tuple with the line end points in any order
@return True if the room is overlapping with the line
*/
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

/*
Returns the vector between two rooms, this and other

@param other A const reference to the other room
@return A vector between the this and the other room
*/
Vec2 Room::GetVectorBetween(const Room& other) const
{
    return Vec2(other.x - x, other.y - y);
}

/*
Moves this room to a direction specified by a vector.
Returns the new position.

@param dir Direction and amount to move the room by
@return New position
*/
Vec2 Room::Move(const Vec2& dir)
{
    x += dir.x;
    y += dir.y;

    return Vec2(x, y);
}

/*
Get all 4 vertices of this room. Used for rendering.

@param scale Scaling factor for the vertices
@return Array of points as two-dimensional vectors
*/
Array<Vec2> Room::GetVertices(float scale) const
{
    Array<Vec2> arr(4);

    arr.Add(Vec2((x - width / 2) * scale, (y - height / 2) * scale));
    arr.Add(Vec2((x - width / 2) * scale, (y + height / 2) * scale));
    arr.Add(Vec2((x + width / 2) * scale, (y + height / 2) * scale));
    arr.Add(Vec2((x + width / 2) * scale, (y - height / 2) * scale));

    return arr;
}

/*
Returns distance to origin from the center point, aka position length

@return Distance to origin
*/
float Room::DistanceToOrigin() const
{
    return Vec2(x, y).Length();
}

/*
Checks if this room is close enough to another room on the x-axis.

@param other Const reference to another room
@return True if the rooms are close enough
*/
bool Room::CloseEnoughX(const Room& other)
{
    const float threshold = 5.0f;
    if (x > other.x)
    {
        return (x - width) - (other.x - width) < threshold;
    }
    else
    {
        return (other.x - width) - (x - width) < threshold;
    }
}

/*
Checks if this room is close enough to another room on the y-axis.

@param other Const reference to another room
@return True if the rooms are close enough
*/
bool Room::CloseEnoughY(const Room& other)
{
    const float threshold = 5.0f;
    if (y > other.y)
    {
        return (y - height) - (other.y - height) < threshold;
    }
    else
    {
        return (other.y - height) - (y - height) < threshold;
    }
}

/*
Overloaded equality operator for Room
Checks for equality on x, y, width and height

@param other Const reference to another room
@return True if the rooms are equal on the specified variables
*/
bool Room::operator==(const Room& other) const
{
    return x == other.x && y == other.y && width == other.width && height == other.height;
}

/*
Overloaded stream operator for Room
Writes x, y, width, height and type (as an int) in json format to ostream

@param os Reference to a stream to output to
@param room Const reference to the room to output
@return os Return os with room in the stream
*/
std::ostream& operator<<(std::ostream& os, const Room& room)
{
    os << '{' << "\"x\": " << room.x << ", \"y\": " << room.y << ", \"width\": " << room.width
       << ", \"height\": " << room.height << ", \"type\": " << (int)room.eRoomType << '}';
    return os;
}
