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
    Renderer::SetGenerator(NULL);
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

    // Assuming fps of 60, thus running update every 0.1s
    if (currentStep == SEPARATE && numUpdates >= 6)
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
        Vec2 pos = Math::GetRandomPointInCircle(circleRadius);

        // Room width and height max half of circle radius and min 4 units
        float roomWidth = Random::GetRandomValue() * (circleRadius / 2.0f) + 4;
        float roomHeight = Random::GetRandomValue() * (circleRadius / 2.0f) + 4;
        rooms.Add(Room(roomWidth, roomHeight, pos.x, pos.y));
    }
}

bool Generator::SeparateRooms()
{
    bool bDone = true;

    // Fuck it we goin O(n^2) for now 
    for (int i = 0; i < rooms.Size(); i++)
    {
        for (int j = 0; j < rooms.Size(); j++)
        {
            // Can't collide with self
            if (i == j)
                continue;

            Room& r1 = rooms[i];
            Room& r2 = rooms[j];

            if (r1.IsColliding(r2))
            {
                if (r1.DistanceToOrigin() > r2.DistanceToOrigin())
                {
                    Vec2 v = r2.GetVectorBetween(r1).Normalized();
                    r1.Move(v);
                }
                else
                {
                    Vec2 v = r1.GetVectorBetween(r2).Normalized();
                    r2.Move(v);
                }
                
                bDone = false;
            }
        }
    }

    return bDone;
}
