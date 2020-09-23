#include "dungeon_generation/data/Triangle.h"

#include "doctest.h"

TEST_SUITE("Test Triangle")
{
    TEST_CASE("Test IsDelaunay")
    {
        std::shared_ptr<Room> a1 = std::make_shared<Room>(1, 1, -3, 3);
        std::shared_ptr<Room> b1 = std::make_shared<Room>(1, 1, -4, -1);
        std::shared_ptr<Room> c1 = std::make_shared<Room>(1, 1, -2, -3);

        Triangle t1(a1, b1, c1);

        std::shared_ptr<Room> a2 = std::make_shared<Room>(1, 1, -2, 3);
        std::shared_ptr<Room> b2 = std::make_shared<Room>(1, 1, 0, 1);
        std::shared_ptr<Room> c2 = std::make_shared<Room>(1, 1, 0, -2);

        Triangle t2(a2, b2, c2);

        Vec2 d(2, 2);

        CHECK(!t1.IsDelaunay(d));
        CHECK(t2.IsDelaunay(d));
    }

    TEST_CASE("Test GetClosestVerts")
    {
        std::shared_ptr<Room> a1 = std::make_shared<Room>(1, 1, -3, 3);
        std::shared_ptr<Room> b1 = std::make_shared<Room>(1, 1, -4, -1);
        std::shared_ptr<Room> c1 = std::make_shared<Room>(1, 1, -2, -3);

        Triangle t1(a1, b1, c1);

        std::shared_ptr<Room> a2 = std::make_shared<Room>(1, 1, -2, 3);
        std::shared_ptr<Room> b2 = std::make_shared<Room>(1, 1, 0, 1);
        std::shared_ptr<Room> c2 = std::make_shared<Room>(1, 1, 0, -2);

        Triangle t2(a2, b2, c2);

        Vec2 point(2, 2);

        Triangle::Edge rest1 = t1.GetClosestVerts(point);
        Triangle::Edge rest2 = t2.GetClosestVerts(point);

        CHECK(*rest1.key == *a1);
        CHECK(*rest1.value == *c1);
        CHECK(*rest2.key == *a2);
        CHECK(*rest2.value == *b2);
    }
}
