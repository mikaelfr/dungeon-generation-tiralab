#include "dungeon_generation/data/Room.h"

#include "doctest.h"

TEST_SUITE("Test Room")
{
    TEST_CASE("Constructor returns a zero room")
    {
        CHECK(Room() == Room(0, 0, 0, 0));
    }

    TEST_CASE("Test collision")
    {
        Room r1(20, 30, 10, 10);
        Room r2(10, 10, 0, 0);
        Room r3(20, 40, 100, 200);

        CHECK(!r1.IsColliding(r3));
        CHECK(r1.IsColliding(r2));
        CHECK(!r2.IsColliding(r3));
    }

    TEST_CASE("Test vertices")
    {
        Room r1(20, 30, 10, 10);
        Array<Vec2> r1Verts = r1.GetVertices();
        CHECK(r1Verts[0] == Vec2(0, -5));
        CHECK(r1Verts[1] == Vec2(0, 25));
        CHECK(r1Verts[2] == Vec2(20, 25));
        CHECK(r1Verts[3] == Vec2(20, -5));
    }

    TEST_CASE("Test vector between")
    {
        Room r1(20, 30, 10, 10);
        Room r2(10, 10, 5, -5);

        CHECK(r1.GetVectorBetween(r2) == Vec2(-5, -15));
        CHECK(r2.GetVectorBetween(r1) == -r1.GetVectorBetween(r2));
    }

    TEST_CASE("Test move")
    {
        Room r1(20, 30, 10, 10);
        Room r2(10, 10, 5, -5);

        CHECK(r1.Move(Vec2(5, -5)) == Vec2(15, 5));
        CHECK(r2.Move(Vec2(0, 10)) == Vec2(5, 5));
        CHECK(r2.Move(Vec2(0, 0)) == Vec2(5, 5));
    }
}
