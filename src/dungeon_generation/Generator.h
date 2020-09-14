#pragma once

#include "data/Array.h"
#include "data/Room.h"

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

    // Hold array here so it need not be passed around constantly
    Array<Room> rooms;
    // Points to rooms in above array
    // Rooms array CANNOT be modified after main rooms have been picked
    // or I'll have to come up with something else
    Array<Room*> mainRooms;

    void GenerateRooms();

    // Returns true if done with separating
    bool SeparateRooms();

    void PickRooms();
};
