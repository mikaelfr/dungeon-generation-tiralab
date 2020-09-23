#pragma once

#include "data/Array.h"
#include "data/Room.h"
#include "data/Triangle.h"

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
        HALLWAYS
    };

    Generator();
    ~Generator();

    void Generate(int seed);
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

    void GenerateRooms();

    // Returns true if done with separating
    bool SeparateRooms();
    void PickRooms();
    void PreGraphRooms();
    bool GraphRooms();
    void PostGraphRooms();
};
