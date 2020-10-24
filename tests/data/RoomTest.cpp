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

    TEST_CASE("Test position and conversion")
    {
        Room r1(20, 30, 10, 10);
        Room r2(10, 10, 5, -5);

        CHECK(Vec2(10, 10) == r1);
        CHECK(Vec2(5, -5) == r2);
    }

    TEST_CASE("Test collision with line")
    {
        Room r1(20, 30, 10, 10);
        Room r2(10, 10, 0, 0);
        Room r3(20, 40, 100, 200);

        Tuple<Vec2, Vec2> l1(Vec2(-20, 0), Vec2(20, 0));
        Tuple<Vec2, Vec2> l2(Vec2(0, -20), Vec2(0, 20));
        Tuple<Vec2, Vec2> l3(Vec2(0, 200), Vec2(400, 200));

        CHECK(r1.IsColliding(l1));
        CHECK(r1.IsColliding(l2));
        CHECK(!r1.IsColliding(l3));

        CHECK(r2.IsColliding(l1));
        CHECK(r2.IsColliding(l2));
        CHECK(!r2.IsColliding(l3));

        CHECK(!r3.IsColliding(l1));
        CHECK(!r3.IsColliding(l2));
        CHECK(r3.IsColliding(l3));
    }

    TEST_CASE("Test close enough")
    {
        Room r1(20, 30, 10, 10);
        Room r2(10, 10, 0, 0);
        Room r3(20, 40, 100, 200);

        CHECK(r1.CloseEnoughX(r2));
        CHECK(r1.CloseEnoughY(r2));
        CHECK(!r1.CloseEnoughX(r3));
        CHECK(!r1.CloseEnoughY(r3));
    }
}
