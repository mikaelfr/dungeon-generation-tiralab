#include "dungeon_generation/util/Math.h"

#include "doctest.h"

TEST_CASE("Test simple math functions") {
	// Test Abs
	SUBCASE("Test Abs")
	{
		CHECK(Math::Abs(1) == 1);
		CHECK(Math::Abs(-3) == 3);
		CHECK(Math::Abs(2.0f) == 2.0f);
		CHECK(Math::Abs(-6.0f) == 6.0f);
		CHECK(Math::Abs(0.0f) == 0.0f);
	}

	/*
	Commenting these away for now,
	library isn't using these functions so compiler is optimizing away
	unused static functions which means we cannot use them here either
	Lovely isn't it!

	// Test Min
	SUBCASE("Test Min")
	{
		CHECK(Math::Min(0.5f, 9.0f) == 0.5f);
		CHECK(Math::Min(1.0f, 1.0f) == 1.0f);
		CHECK(Math::Min(-6.0f, 4.0f) == -6.0f);
	}

	// Test Max
	SUBCASE("Test Max")
	{
		CHECK(Math::Max(0.5f, 9.0f) == 9.0f);
		CHECK(Math::Max(1.0f, 1.0f) == 1.0f);
		CHECK(Math::Max(-6.0f, 4.0f) == 4.0f);
	}*/
}
