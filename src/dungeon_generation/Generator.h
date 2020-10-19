#pragma once

#include "data/Array.h"
#include "data/Room.h"
#include "data/Triangle.h"
#include "data/Set.h"

/*
Class directing the main flow of the generation
*/
class Generator
{
public:
    enum GenerationStep
    {
        NOT_STARTED = 0,
        GENERATE,
        SEPARATE,
        PICKING,
        GRAPHING,
        SPANNING_TREE,
        HALLWAYS,
        DONE
    };

    typedef Tuple<Vec2, Vec2> Line;

    Generator();
    ~Generator();

    void Generate(int seed, bool bHeadless);
    void Update();

private:
    const int numRoomCandidates = 300;
    const int circleRadius = 64;

    int numUpdates = 0;
    GenerationStep currentStep = NOT_STARTED;
    int stepNumber = 0;

    // Hold array here so it need not be passed around constantly
    Array<std::shared_ptr<Room>> rooms;
    Array<std::shared_ptr<Room>> mainRooms;
    Array<std::shared_ptr<Triangle>> triangles;
    Set<Edge> edges;
    Array<Edge> selectedEdges;
    Array<Line> lines;

    void GenerateRooms();

    // Returns true if done with separating
    bool SeparateRooms();
    void PickRooms();
    void PreGraphRooms();
    bool GraphRooms();
    void PostGraphRooms();
    void MinimumSpanningTree();
    void GenerateHallways();
    void PrintOutput();
};
