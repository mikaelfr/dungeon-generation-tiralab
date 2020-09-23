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
    Renderer::SetRoomArray(&rooms, &triangles);
    Renderer::Init(this);
}

void Generator::Update()
{
    numUpdates++;

    // Intentionally placing these in reverse order
    // so steps is run on the next update
    if (currentStep == GRAPHING && numUpdates >= 30)
    {
        numUpdates = 0;
        if (GraphRooms())
        {
            PostGraphRooms();
            currentStep = HALLWAYS;
        }
    }

    if (currentStep == PICKING)
    {
        PickRooms();
        PreGraphRooms();
        currentStep = GRAPHING;
    }

    // Assuming fps of 60, thus running update every 0.1s
    if (currentStep == SEPARATE && numUpdates >= 6)
    {
        numUpdates = 0;
        if (SeparateRooms())
            currentStep = PICKING;
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
        rooms.Add(std::make_shared<Room>(roomWidth, roomHeight, pos.x, pos.y));
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

            std::shared_ptr<Room>& r1 = rooms[i];
            std::shared_ptr<Room>& r2 = rooms[j];

            if (r1->IsColliding(*r2))
            {
                if (r1->DistanceToOrigin() > r2->DistanceToOrigin())
                {
                    Vec2 v = r2->GetVectorBetween(*r1).Normalized();
                    r1->Move(v);
                }
                else
                {
                    Vec2 v = r1->GetVectorBetween(*r2).Normalized();
                    r2->Move(v);
                }

                bDone = false;
            }
        }
    }

    return bDone;
}

void Generator::PickRooms()
{
    rooms.Sort([](const std::shared_ptr<Room>& a, const std::shared_ptr<Room>& b) { return (int)(b->width - a->width); });
    float widthMean = rooms[(int)(rooms.Size() / 2)]->width;

    rooms.Sort([](const std::shared_ptr<Room>& a, const std::shared_ptr<Room>& b) { return (int)(b->height - a->height); });
    float heightMean = rooms[(int)(rooms.Size() / 2)]->height;

    // Pick rooms larger than 1.25 times the mean in width and height
    for (std::shared_ptr<Room>& r : rooms)
    {
        if (r->width > 1.25f * widthMean && r->height > 1.25f * heightMean)
        {
            r->bMainRoom = true;
            mainRooms.Add(r);
        }
    }
}

void Generator::PreGraphRooms()
{
    float minX = mainRooms[0]->x;
    float minY = mainRooms[0]->y;
    float maxX = mainRooms[0]->x;
    float maxY = mainRooms[0]->y;

    for (const std::shared_ptr<Room>& room : mainRooms)
    {
        minX = Math::Min(minX, room->x);
        minY = Math::Min(minY, room->y);
        maxX = Math::Max(maxX, room->x);
        maxY = Math::Max(maxY, room->y);
    }

    float extentX = maxX - minX;
    float extentY = maxY - minY;
    float maxExtent = Math::Max(extentX, extentY);
    float midX = (maxX + minX) / 2;
    float midY = (maxY + minY) / 2;

    // Constructing "broken" rooms with width and height of -1
    std::shared_ptr<Room> r1 = std::make_shared<Room>(-1, -1, midX - 20 * maxExtent, midY - maxExtent);
    std::shared_ptr<Room> r2 = std::make_shared<Room>(-1, -1, midX, midY + 20 * maxExtent);
    std::shared_ptr<Room> r3 = std::make_shared<Room>(-1, -1, midX + 20 * maxExtent, midY - maxExtent);

    triangles.Add(std::make_shared<Triangle>(r1, r2, r3));
}

// Using Bowyer-Watson algorithm avg. O(n log n), max. O(n^2)
bool Generator::GraphRooms()
{
    std::shared_ptr<Room> room = mainRooms[stepNumber++];

    Array<std::shared_ptr<Triangle>> badTriangles;

    for (std::shared_ptr<Triangle>& t : triangles)
    {
        if (!t->IsDelaunay(*room))
        {
            badTriangles.Add(t);
        }
    }

    Array<Triangle::Edge> polygon;

    for (std::shared_ptr<Triangle>& t : badTriangles)
    {
        for (Triangle::Edge& e : t->GetEdges())
        {
            bool sharedByBadTriangle = false;
            for (std::shared_ptr<Triangle>& bt : badTriangles)
            {
                // Looking at all OTHER triangles
                if (t == bt)
                    continue;

                if (bt->HasEdge(e))
                {
                    sharedByBadTriangle = true;
                    break;
                }
            }

            if (!sharedByBadTriangle)
                polygon.Add(e);
        }
    }

    for (std::shared_ptr<Triangle>& t : badTriangles)
    {
        triangles.Remove(t);
    }

    for (Triangle::Edge& edge : polygon)
    {
        triangles.Add(std::make_shared<Triangle>(edge.key, room, edge.value));
    }

    if (stepNumber == mainRooms.Size())
        return true;

    return false;
}

void Generator::PostGraphRooms()
{
    Array<std::shared_ptr<Triangle>> badTriangles;

    for (const std::shared_ptr<Triangle>& t : triangles)
    {
        if (t->HasVertFromSuperTriangle())
            badTriangles.Add(t);
    }

    for (const std::shared_ptr<Triangle>& t : badTriangles)
    {
        triangles.Remove(t);
    }
}
