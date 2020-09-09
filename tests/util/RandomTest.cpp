#include "dungeon_generation/util/Random.h"

#include "doctest.h"

bool CheckEpsilon(float value, float target, float epsilon = 0.001f)
{
	return value < target + epsilon && value > target - epsilon;
}

TEST_SUITE("Test Random class")
{
	TEST_CASE("Test GetRandomValue")
	{
		Random::SetSeed(0xBEEF);

		CHECK(CheckEpsilon(Random::GetRandomValue(), 0.943116f));
		CHECK(CheckEpsilon(Random::GetRandomValue(), 0.314125f));
		CHECK(CheckEpsilon(Random::GetRandomValue(), 0.627954f));
		CHECK(CheckEpsilon(Random::GetRandomValue(), 0.102516f));
		CHECK(CheckEpsilon(Random::GetRandomValue(), 0.335745f));
		CHECK(CheckEpsilon(Random::GetRandomValue(), 0.600048f));
		CHECK(CheckEpsilon(Random::GetRandomValue(), 0.0351989f));
		CHECK(CheckEpsilon(Random::GetRandomValue(), 0.0369739f));
		CHECK(CheckEpsilon(Random::GetRandomValue(), 0.109422f));
		CHECK(CheckEpsilon(Random::GetRandomValue(), 0.027918f));
	}
}