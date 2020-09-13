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
        NEXT
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

    void GenerateRooms();

    // Returns true if done with separating
    bool SeparateRooms();
};
