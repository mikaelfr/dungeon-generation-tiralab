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
        Array<Vec2i> r1Verts = r1.GetVertices();
        CHECK(r1Verts[0] == Vec2i(0, -5));
        CHECK(r1Verts[1] == Vec2i(0, 25));
        CHECK(r1Verts[2] == Vec2i(20, 25));
        CHECK(r1Verts[3] == Vec2i(20, -5));
    }
}
