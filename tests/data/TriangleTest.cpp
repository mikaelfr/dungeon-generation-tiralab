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

    TEST_CASE("Test HasVertFromSuperTriangle")
    {
        std::shared_ptr<Room> a1 = std::make_shared<Room>(1, 1, -3, 3);
        std::shared_ptr<Room> b1 = std::make_shared<Room>(1, 1, -4, -1);
        std::shared_ptr<Room> c1 = std::make_shared<Room>(1, 1, -2, -3);

        Triangle t1(a1, b1, c1);

        std::shared_ptr<Room> a2 = std::make_shared<Room>(1, -1, -2, 3);
        std::shared_ptr<Room> b2 = std::make_shared<Room>(1, 1, 0, 1);
        std::shared_ptr<Room> c2 = std::make_shared<Room>(-1, -1, 0, -2);

        Triangle t2(a2, b2, c2);

        CHECK(!t1.HasVertFromSuperTriangle());
        CHECK(t2.HasVertFromSuperTriangle());
    }

    TEST_CASE("Test HasEdge")
    {
        std::shared_ptr<Room> a1 = std::make_shared<Room>(1, 1, -3, 3);
        std::shared_ptr<Room> b1 = std::make_shared<Room>(1, 1, -4, -1);
        std::shared_ptr<Room> c1 = std::make_shared<Room>(1, 1, -2, -3);

        Triangle::Edge e11 = Triangle::Edge(a1, b1);
        Triangle::Edge e12 = Triangle::Edge(b1, c1);
        Triangle::Edge e13 = Triangle::Edge(c1, a1);

        Triangle t1(a1, b1, c1);

        std::shared_ptr<Room> a2 = std::make_shared<Room>(1, -1, -2, 3);
        std::shared_ptr<Room> b2 = std::make_shared<Room>(1, 1, 0, 1);
        std::shared_ptr<Room> c2 = std::make_shared<Room>(-1, -1, 0, -2);

        Triangle::Edge e21 = Triangle::Edge(a2, b2);
        Triangle::Edge e22 = Triangle::Edge(b2, c2);
        Triangle::Edge e23 = Triangle::Edge(c2, a2);

        Triangle t2(a2, b2, c2);

        CHECK(t1.HasEdge(e11));
        CHECK(t1.HasEdge(e12));
        CHECK(t1.HasEdge(e13));

        CHECK(t2.HasEdge(e21));
        CHECK(t2.HasEdge(e22));
        CHECK(t2.HasEdge(e23));
    }

    TEST_CASE("Test GetVerts")
    {
        std::shared_ptr<Room> a1 = std::make_shared<Room>(1, 1, -3, 3);
        std::shared_ptr<Room> b1 = std::make_shared<Room>(1, 1, -4, -1);
        std::shared_ptr<Room> c1 = std::make_shared<Room>(1, 1, -2, -3);

        Triangle t1(a1, b1, c1);

        Verts v = t1.GetVerts();
        Verts::iterator it = v.begin();
        CHECK(a1 == *it);
        ++it;
        CHECK(b1 == *it);
        ++it;
        CHECK(c1 == *it);
        ++it;
        CHECK_FALSE(it != v.end());
    }

    TEST_CASE("Test GetEdges")
    {
        std::shared_ptr<Room> a1 = std::make_shared<Room>(1, 1, -3, 3);
        std::shared_ptr<Room> b1 = std::make_shared<Room>(1, 1, -4, -1);
        std::shared_ptr<Room> c1 = std::make_shared<Room>(1, 1, -2, -3);

        Triangle::Edge e1 = Triangle::Edge(a1, b1);
        Triangle::Edge e2 = Triangle::Edge(b1, c1);
        Triangle::Edge e3 = Triangle::Edge(c1, a1);

        Triangle t1(a1, b1, c1);

        Edges e = t1.GetEdges();
        Edges::iterator it = e.begin();
        CHECK(e1.key == (*it).key);
        CHECK(e1.value == (*it).value);
        ++it;
        CHECK(e2.key == (*it).key);
        CHECK(e2.value == (*it).value);
        ++it;
        CHECK(e3.key == (*it).key);
        CHECK(e3.value == (*it).value);
        ++it;
        CHECK_FALSE(it != e.end());
    }
}
