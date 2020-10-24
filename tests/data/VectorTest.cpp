#include "dungeon_generation/data/Vector.h"

#include "doctest.h"
#include <sstream>

TEST_SUITE("Test Vector")
{
    TEST_CASE("Constructor returns zero vector")
    {
        CHECK(Vec2() == Vec2(0, 0));
    }

    TEST_CASE("Test zero vector")
    {
        Vec2 vec = Vec2(0, 0);

        CHECK(vec.Length() == 0);
        CHECK(vec.Normalized() == Vec2(0, 0));
    }

    TEST_CASE("Test vector length")
    {
        CHECK(Vec2(0, 1).Length() == 1);
        CHECK(Vec2(1, 0).Length() == 1);
        CHECK(Vec2(-1, 0).Length() == 1);
        CHECK(Vec2(0, -1).Length() == 1);
        CHECK(Vec2(8, 0).Length() == 8);
        CHECK(Vec2(0, -9).Length() == 9);
    }

    TEST_CASE("Test vector normalization")
    {
        CHECK(Vec2(1, 0).Normalized() == Vec2(1, 0));
        CHECK(Vec2(2, 0).Normalized() == Vec2(1, 0));
        CHECK(Vec2(0, 1).Normalized() == Vec2(0, 1));
        CHECK(Vec2(0, 2).Normalized() == Vec2(0, 1));
        CHECK(Vec2(-1, 0).Normalized() == Vec2(-1, 0));
        CHECK(Vec2(-2, 0).Normalized() == Vec2(-1, 0));
        CHECK(Vec2(0, -1).Normalized() == Vec2(0, -1));
        CHECK(Vec2(0, -2).Normalized() == Vec2(0, -1));
    }

    TEST_CASE("Test vector addition")
    {
        CHECK(Vec2(0, 0) + Vec2(0, 0) == Vec2(0, 0));
        CHECK(Vec2(6, 4) + Vec2(3, 7) == Vec2(9, 11));
        CHECK(Vec2(-5, 90) + Vec2(7, -100) == Vec2(2, -10));
        CHECK(Vec2(10, 0) + Vec2(0, 3) == Vec2(10, 3));
        CHECK(Vec2(-8, -5) + Vec2(-4, -7) == Vec2(-12, -12));
        CHECK(Vec2(9, 5) + Vec2(-5, -9) == Vec2(4, -4));
    }

    TEST_CASE("Test vector subtraction")
    {
        CHECK(Vec2(0, 0) - Vec2(0, 0) == Vec2(0, 0));
        CHECK(Vec2(6, 4) - Vec2(3, 7) == Vec2(3, -3));
        CHECK(Vec2(-5, 90) - Vec2(7, -100) == Vec2(-12, 190));
        CHECK(Vec2(10, 0) - Vec2(0, 3) == Vec2(10, -3));
        CHECK(Vec2(-8, -5) - Vec2(-4, -7) == Vec2(-4, 2));
        CHECK(Vec2(9, 5) - Vec2(-5, -9) == Vec2(14, 14));
    }

    TEST_CASE("Test vector multiplication by scalar")
    {
        CHECK(Vec2(2, 3) * 1 == Vec2(2, 3));
        CHECK(Vec2(5, 6) * 2.0f == Vec2(10, 12));
        CHECK(Vec2(-5, -6) * -2 == Vec2(10, 12));
        CHECK(Vec2(4, 2) * 1.5f == Vec2(6, 3));
    }

    TEST_CASE("Test stream operator")
    {
        std::stringstream ss;
        ss << Vec2(-4, 3);
        CHECK(ss.str() == "{\"x\": -4, \"y\": 3}");
        ss.str("");
        ss << Vec2(0, -3.5f);
        CHECK(ss.str() == "{\"x\": 0, \"y\": -3.5}");
    }
}
