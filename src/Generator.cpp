#include "Generator.h"
#include "util/Random.h"
#include "util/Math.h"

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
	// Sort by x axis and run step
	rooms.Sort([](const Room& a, const Room& b) { return b.x - a.x; });
	for (Room& r : rooms)
	{

	}
}


