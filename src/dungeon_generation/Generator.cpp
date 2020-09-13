#include "Generator.h"
#include "util/Random.h"
#include "util/Math.h"
#include "data/Tuple.h"
#include "ui/Renderer.h"

Generator::Generator()
    : rooms(numRoomCandidates)
{
}

Generator::~Generator()
{
    Renderer::SetGenerator(false);
}

void Generator::Generate(int seed)
{
    Random::SetSeed(seed);
    currentStep = GENERATE;
    GenerateRooms();

    currentStep = SEPARATE;
    Renderer::SetRoomArray(&rooms);
    Renderer::Init(this);
}

void Generator::Update()
{
    numUpdates++;

    // Assuming fps of 60, thus running update every 0.5s
    if (currentStep == SEPARATE && numUpdates >= 30)
    {
        numUpdates = 0;
        if (SeparateRooms())
            currentStep = NEXT;
    }
}

void Generator::GenerateRooms()
{
    // Generate <numRoomCandidates> candidates for rooms
    for (int i = 0; i < numRoomCandidates; i++)
    {
        Vec2i pos = Math::GetRandomPointInCircle(circleRadius);

        // Room width and height max half of circle radius and min 4 units
        int roomWidth = (int)(Random::GetRandomValue() * (circleRadius / 2.0f) + 4);
        int roomHeight = (int)(Random::GetRandomValue() * (circleRadius / 2.0f) + 4);
        rooms.Add(Room(roomWidth, roomHeight, pos.x, pos.y));
    }
}

bool Generator::SeparateRooms()
{
    bool bDone = true;
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
            bDone = false;
        }
    }

    return bDone;
}
