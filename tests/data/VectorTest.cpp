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

    TEST_CASE("Test vector addition")
    {
        CHECK(Vec2i(0, 0) + Vec2i(0, 0) == Vec2i(0, 0));
        CHECK(Vec2i(6, 4) + Vec2i(3, 7) == Vec2i(9, 11));
        CHECK(Vec2i(-5, 90) + Vec2i(7, -100) == Vec2i(2, -10));
        CHECK(Vec2i(10, 0) + Vec2i(0, 3) == Vec2i(10, 3));
        CHECK(Vec2i(-8, -5) + Vec2i(-4, -7) == Vec2i(-12, -12));
        CHECK(Vec2i(9, 5) + Vec2i(-5, -9) == Vec2i(4, -4));
    }

    TEST_CASE("Test vector subtraction")
    {
        CHECK(Vec2i(0, 0) - Vec2i(0, 0) == Vec2i(0, 0));
        CHECK(Vec2i(6, 4) - Vec2i(3, 7) == Vec2i(3, -3));
        CHECK(Vec2i(-5, 90) - Vec2i(7, -100) == Vec2i(-12, 190));
        CHECK(Vec2i(10, 0) - Vec2i(0, 3) == Vec2i(10, -3));
        CHECK(Vec2i(-8, -5) - Vec2i(-4, -7) == Vec2i(-4, 2));
        CHECK(Vec2i(9, 5) - Vec2i(-5, -9) == Vec2i(14, 14));
    }
}
