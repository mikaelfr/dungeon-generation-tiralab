#include "Generator.h"
#include "util/Random.h"
#include "util/Math.h"
#include "data/Tuple.h"
#include "ui/Renderer.h"

/*
Constructor for the generator

Initializes the rooms array to hold the amount of rooms to be generated
so the array doesn't have to be resized multiple times over generation
*/
Generator::Generator()
    : rooms(numRoomCandidates)
{
}

/*
Destructor for the generator

Sets the references to the generator in Renderer to null
*/
Generator::~Generator()
{
    Renderer::SetGenerator(NULL);
    Renderer::SetRoomArray(NULL, NULL, NULL, NULL);
}

/*
Deterministically generates a dungeon from a given seed

@param seed Seed for dungeon generation
@param bHeadless If true, UI is not initialized
*/
void Generator::Generate(int seed, bool bHeadless)
{
    Random::SetSeed(seed);

    if (!bHeadless)
    {
        currentStep = GENERATE;
        GenerateRooms();
        Renderer::SetRoomArray(&rooms, &triangles, &selectedEdges, &lines);
        Renderer::Init(this);
    }
    else
    {
        GenerateRooms();
        bool bDone = false;
        while (!bDone)
            bDone = SeparateRooms();
        PickRooms();
        PreGraphRooms();
        bDone = false;
        while (!bDone)
            bDone = GraphRooms();
        PostGraphRooms();
        MinimumSpanningTree();
        GenerateHallways();
        PrintOutput();
    }
}

/*
Update function to be called by the renderer

Assumes 60 fps
*/
void Generator::Update()
{
    if (!Renderer::ShouldRunStep() && currentStep != SEPARATE)
        return;

    Renderer::StepRan();
    numUpdates++;

    // Intentionally placing these in reverse order
    // so steps are run on the next update
    if (currentStep == PRINTING)
    {
        PrintOutput();
        Renderer::SetFinished(true);
        currentStep = DONE;
    }

    if (currentStep == HALLWAYS)
    {
        GenerateHallways();
        currentStep = PRINTING;
    }

    if (currentStep == SPANNING_TREE)
    {
        MinimumSpanningTree();
        currentStep = HALLWAYS;
    }

    if (currentStep == GRAPHING)
    {
        if (GraphRooms())
        {
            PostGraphRooms();
            currentStep = SPANNING_TREE;
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

    // Just having this here so we can stop before the separation step
    if (currentStep == GENERATE)
    {
        currentStep = SEPARATE;
    }
}

/*
Generates different size rooms in a circle.

Picks a random point in a circle with radius of circleRadius (const int defined in Generator.h)
and spawns a random sized room in that spot
*/
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

/*
Uses a simple AABB collision detection algorithm with dumb O(n^2) resolving
to separate rooms so that none are overlapping

@return True if no rooms are colliding anymore
*/
bool Generator::SeparateRooms()
{
    bool bDone = true;

    // Fuck it we goin O(n^2) for now
    // Broadphasing might be faster
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

/*
Picks main rooms from all rooms by selecting rooms with width and height larger than 1.25 * median width and height

Uses O(n log n) merge sort from Array class to order rooms by width and height
*/
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
            r->eRoomType = Room::MAIN;
            mainRooms.Add(r);
        }
    }
}

/*
Sets up a triangle large enough to encompass all rooms for Bowyer-Watson algorithm
*/
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
    std::shared_ptr<Room> r1 = std::make_shared<Room>(-1.0f, -1.0f, midX - 20 * maxExtent, midY - maxExtent);
    std::shared_ptr<Room> r2 = std::make_shared<Room>(-1.0f, -1.0f, midX, midY + 20 * maxExtent);
    std::shared_ptr<Room> r3 = std::make_shared<Room>(-1.0f, -1.0f, midX + 20 * maxExtent, midY - maxExtent);

    triangles.Add(std::make_shared<Triangle>(r1, r2, r3));
}

/*
Creates a "beautiful" triangulation of all rooms

Beautiful defined as all triangles meeting the Delaunay condition

Delaunay condition states that for every triangle, the circle drawn over all three of the vertices
of the triangle should not have any vertex in it other than the three defining the circle

Uses Bowyer-Watson algorithm avg. O(n log n), max. O(n^2)

@return True if graphing finished
*/
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

    Array<Edge> polygon;

    for (std::shared_ptr<Triangle>& t : badTriangles)
    {
        for (Edge e : t->GetEdges())
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

    for (Edge& edge : polygon)
    {
        triangles.Add(std::make_shared<Triangle>(edge.key, room, edge.value));
    }

    if (stepNumber == mainRooms.Size())
        return true;

    return false;
}

/*
Removes all triangles that contains a vertex from the super triangle 
In addition, creates a set of unique edges from triangles

Super triangle refers to the one created in PreGraphRooms that encompasses all rooms
*/
void Generator::PostGraphRooms()
{
    Array<std::shared_ptr<Triangle>> badTriangles;

    // Remove bad triangles and create adjacency lists
    for (const std::shared_ptr<Triangle>& t : triangles)
    {
        if (t->HasVertFromSuperTriangle())
        {
            badTriangles.Add(t);
        }
        else
        {
            // Set guarantees we will not have duplicate edges
            edges.Add(Edge(t->a, t->b), Edge(t->b, t->c), Edge(t->c, t->a));

            t->a->neighbors.Add(t->b, t->c);
            t->b->neighbors.Add(t->a, t->c);
            t->c->neighbors.Add(t->a, t->b);
        }
    }

    for (const std::shared_ptr<Triangle>& t : badTriangles)
    {
        triangles.Remove(t);
    }
}

/*
Creates the (almost) minimum spanning tree from the triangulation
Includes 10% extra edges for more interesting looking dungeon

Uses Kruskal's algorithm
*/
void Generator::MinimumSpanningTree()
{
    edges.Sort([](const Edge& a, const Edge& b) { return (int)(a.key->GetVectorBetween(*a.value).Length() < b.key->GetVectorBetween(*b.value).Length()); });
    for (Edge& e : edges)
    {
        if (e.key->set.Find() != e.value->set.Find())
        {
            selectedEdges.Add(e);
            e.key->set += e.value->set;
        }
        else
        {
            // 10% chance to add it anyway for more interesting looking dungeon
            if (Random::GetRandomValue() < 0.1f)
            {
                selectedEdges.Add(e);
            }
        }
    }
}

/*
Generates hallways along the axes between connected main rooms

Picks extra rooms that are close enough to hallways
*/
void Generator::GenerateHallways()
{
    for (const Edge& e : selectedEdges)
    {
        if (e.key->CloseEnoughX(*e.value))
        {
            float xMid = (e.key->x + e.value->x) / 2;
            lines.Add(Line(Vec2(xMid, e.key->y), Vec2(xMid, e.value->y)));
        }
        else if (e.key->CloseEnoughY(*e.value))
        {
            float yMid = (e.key->y + e.value->y) / 2;
            lines.Add(Line(Vec2(e.key->x, yMid), Vec2(e.value->x, yMid)));
        }
        else
        {
            Vec2 corner1(e.key->x, e.value->y);
            Vec2 corner2(e.value->x, e.key->y);
            lines.Add(Line(*e.key, corner1));
            lines.Add(Line(*e.key, corner2));
            lines.Add(Line(*e.value, corner1));
            lines.Add(Line(*e.value, corner2));
        }
    }

    // Going for O(nm) for now
    // Broadphasing might be possible here
    for (std::shared_ptr<Room>& r : rooms)
    {
        // Skipping main rooms
        if (r->eRoomType == Room::MAIN)
            continue;

        for (const Line& l : lines)
        {
            if (r->IsColliding(l))
            {
                // Add to as a hallway and break (since it's already colliding with one)
                r->eRoomType = Room::HALLWAY;
                mainRooms.Add(r);
                break;
            }
        }
    }
}

/*
Prints the dungeon in a json format
*/
void Generator::PrintOutput()
{
    std::cout << '{' << "\"rooms\": " << mainRooms << ", \"lines\": " << lines << '}';
}
