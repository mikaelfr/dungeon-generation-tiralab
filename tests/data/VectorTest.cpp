#include "dungeon_generation/data/Vector.h"

#include "doctest.h"

TEST_SUITE("Test Vector")
{
    TEST_CASE("Constructor returns zero vector")
    {
        CHECK(Vec2i() == Vec2i(0, 0));
    }

    TEST_CASE("Test zero vector")
    {
        Vec2i vec = Vec2i(0, 0);

        CHECK(vec.Length() == 0);
        CHECK(vec.Normalized() == Vec2i(0, 0));
    }

    TEST_CASE("Test vector length")
    {
        CHECK(Vec2i(0, 1).Length() == 1);
        CHECK(Vec2i(1, 0).Length() == 1);
        CHECK(Vec2i(-1, 0).Length() == 1);
        CHECK(Vec2i(0, -1).Length() == 1);
        CHECK(Vec2i(8, 0).Length() == 8);
        CHECK(Vec2i(0, -9).Length() == 9);
    }

    TEST_CASE("Test vector normalization")
    {
        CHECK(Vec2i(1, 0).Normalized() == Vec2i(1, 0));
        CHECK(Vec2i(2, 0).Normalized() == Vec2i(1, 0));
        CHECK(Vec2i(0, 1).Normalized() == Vec2i(0, 1));
        CHECK(Vec2i(0, 2).Normalized() == Vec2i(0, 1));
        CHECK(Vec2i(-1, 0).Normalized() == Vec2i(-1, 0));
        CHECK(Vec2i(-2, 0).Normalized() == Vec2i(-1, 0));
        CHECK(Vec2i(0, -1).Normalized() == Vec2i(0, -1));
        CHECK(Vec2i(0, -2).Normalized() == Vec2i(0, -1));
    }
}
