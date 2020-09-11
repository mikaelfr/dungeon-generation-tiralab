#include "Generator.h"
#include "util/Random.h"
#include "util/Math.h"
#include "data/Tuple.h"

Generator::Generator() : rooms(numRoomCandidates)
{
}

Generator::~Generator()
{
}

void Generator::Generate(int seed)
{
    Random::SetSeed(seed);
    GenerateRooms();
    SeparateRooms();
}

void Generator::GenerateRooms()
{
    // Generate <numRoomCandidates> candidates for rooms
    for (int i = 0; i < numRoomCandidates; i++)
    {
        Vec2i pos = Math::GetRandomPointInCircle(circleRadius);

        // Room width and height max 1/10th of circle radius
        int roomWidth = (int)(Random::GetRandomValue() * (circleRadius / 10.0f));
        int roomHeight = (int)(Random::GetRandomValue() * (circleRadius / 10.0f));
        rooms.Add(Room(roomWidth, roomHeight, pos.x, pos.y));
    }
}

void Generator::SeparateRooms()
{
    bool moving = true;

    while (moving)
    {
        moving = false;
        // Sort by x axis and run step
        rooms.Sort([](const Room& a, const Room& b) { return b.x - a.x; });
        for (int i = 0; i < rooms.Size() - 1; i++)
        {
            Room& r1 = rooms[i];
            Room& r2 = rooms[i + 1];

            if (r1.IsColliding(r2))
            {
                Vec2i v = r1.GetVectorBetween(r2).Normalized();
                r1.Move(v);
                moving = true;
            }
        }
    }
}


