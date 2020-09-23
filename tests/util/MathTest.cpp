#include "dungeon_generation/util/Math.h"

#include "doctest.h"

TEST_SUITE("Test Math")
{
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

        // Test Min
        SUBCASE("Test Min")
        {
            CHECK(Math::Min(0.5f, 9.0f) == 0.5f);
            CHECK(Math::Min(1.0f, 1.0f) == 1.0f);
            CHECK(Math::Min(-6.0f, 4.0f) == -6.0f);

            CHECK(Math::Min(1, 9) == 1);
            CHECK(Math::Min(1, 1) == 1);
            CHECK(Math::Min(-6, 4) == -6);
        }

        // Test Max
        SUBCASE("Test Max")
        {
            CHECK(Math::Max(0.5f, 9.0f) == 9.0f);
            CHECK(Math::Max(1.0f, 1.0f) == 1.0f);
            CHECK(Math::Max(-6.0f, 4.0f) == 4.0f);

            CHECK(Math::Max(1, 9) == 9);
            CHECK(Math::Max(1, 1) == 1);
            CHECK(Math::Max(-6, 4) == 4);
        }
    }

    TEST_CASE("Test GetRandomPointInCircle")
    {
        for (int i = 0; i < 10; i++)
        {
            Vec2 p = Math::GetRandomPointInCircle(10);
            float length = (p - Vec2(0, 0)).Length();
            CHECK(length <= 10);
        }
    }

    TEST_CASE("Test IsClockwise")
    {
        Vec2 a1(-3, 3);
        Vec2 b1(-4, -1);
        Vec2 c1(-2, -3);

        CHECK(!Math::IsClockwise(a1, b1, c1));
        CHECK(Math::IsClockwise(c1, b1, a1));

        Vec2 a2(-2, 3);
        Vec2 b2(0, 1);
        Vec2 c2(0, -2);

        CHECK(Math::IsClockwise(a2, b2, c2));
        CHECK(!Math::IsClockwise(c2, b2, a2));
    }

    TEST_CASE("Test Determinant")
    {
        Vec2 a1(-3, 3);
        Vec2 b1(-4, -1);
        Vec2 c1(-2, -3);

        Vec2 a2(-2, 3);
        Vec2 b2(0, 1);
        Vec2 c2(0, -2);

        Vec2 point(2, 2);

        CHECK(Math::Determinant(a1, b1, c1, point) == 24);
        CHECK(Math::Determinant(c2, b2, a2, point) == -132);
    }
}
