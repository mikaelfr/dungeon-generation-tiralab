#pragma once

#include "data/Array.h"
#include "data/Room.h"

class Generator
{
public:
    Generator();
    ~Generator();

    void Generate(int seed);

private:
    const int numRoomCandidates = 300;
    const int circleRadius = 512;

    // Hold array here so it need not be passed around constantly
    Array<Room> rooms;

    void GenerateRooms();
    void SeparateRooms();

};
