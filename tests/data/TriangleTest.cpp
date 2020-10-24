#include "dungeon_generation/data/Triangle.h"

#include "doctest.h"

TEST_SUITE("Test Triangle")
{
    TEST_CASE("Test Edge")
    {
        SUBCASE("Test Equality")
        {

        }
    }

    TEST_CASE("Test IsDelaunay")
    {
        std::shared_ptr<Room> a1 = std::make_shared<Room>(1.0f, 1.0f, -3.0f, 3.0f);
        std::shared_ptr<Room> b1 = std::make_shared<Room>(1.0f, 1.0f, -4.0f, -1.0f);
        std::shared_ptr<Room> c1 = std::make_shared<Room>(1.0f, 1.0f, -2.0f, -3.0f);

        Triangle t1(a1, b1, c1);

        std::shared_ptr<Room> a2 = std::make_shared<Room>(1.0f, 1.0f, -2.0f, 3.0f);
        std::shared_ptr<Room> b2 = std::make_shared<Room>(1.0f, 1.0f, 0.0f, 1.0f);
        std::shared_ptr<Room> c2 = std::make_shared<Room>(1.0f, 1.0f, 0.0f, -2.0f);

        Triangle t2(a2, b2, c2);

        Vec2 d(2, 2);

        CHECK(!t1.IsDelaunay(d));
        CHECK(t2.IsDelaunay(d));
    }

    TEST_CASE("Test HasVertFromSuperTriangle")
    {
        std::shared_ptr<Room> a1 = std::make_shared<Room>(1.0f, 1.0f, -3.0f, 3.0f);
        std::shared_ptr<Room> b1 = std::make_shared<Room>(1.0f, 1.0f, -4.0f, -1.0f);
        std::shared_ptr<Room> c1 = std::make_shared<Room>(1.0f, 1.0f, -2.0f, -3.0f);

        Triangle t1(a1, b1, c1);

        std::shared_ptr<Room> a2 = std::make_shared<Room>(1.0f, -1.0f, -2.0f, 3.0f);
        std::shared_ptr<Room> b2 = std::make_shared<Room>(1.0f, 1.0f, 0.0f, 1.0f);
        std::shared_ptr<Room> c2 = std::make_shared<Room>(-1.0f, -1.0f, 0.0f, -2.0f);

        Triangle t2(a2, b2, c2);

        CHECK(!t1.HasVertFromSuperTriangle());
        CHECK(t2.HasVertFromSuperTriangle());
    }

    TEST_CASE("Test HasEdge")
    {
        std::shared_ptr<Room> a1 = std::make_shared<Room>(1.0f, 1.0f, -3.0f, 3.0f);
        std::shared_ptr<Room> b1 = std::make_shared<Room>(1.0f, 1.0f, -4.0f, -1.0f);
        std::shared_ptr<Room> c1 = std::make_shared<Room>(1.0f, 1.0f, -2.0f, -3.0f);

        Edge e11 = Edge(a1, b1);
        Edge e12 = Edge(b1, c1);
        Edge e13 = Edge(c1, a1);

        Triangle t1(a1, b1, c1);

        std::shared_ptr<Room> a2 = std::make_shared<Room>(1.0f, -1.0f, -2.0f, 3.0f);
        std::shared_ptr<Room> b2 = std::make_shared<Room>(1.0f, 1.0f, 0.0f, 1.0f);
        std::shared_ptr<Room> c2 = std::make_shared<Room>(-1.0f, -1.0f, 0.0f, -2.0f);

        Edge e21 = Edge(a2, b2);
        Edge e22 = Edge(c2, b2);
        Edge e23 = Edge(c2, a2);

        Edge e31 = Edge(c2, a2);

        Triangle t2(a2, b2, c2);

        CHECK(t1.HasEdge(e11));
        CHECK(t1.HasEdge(e12));
        CHECK(t1.HasEdge(e13));
        CHECK(!t1.HasEdge(e23));

        CHECK(t2.HasEdge(e21));
        CHECK(t2.HasEdge(e22));
        CHECK(t2.HasEdge(e23));
        CHECK(!t2.HasEdge(e11));
    }

    TEST_CASE("Test GetVerts")
    {
        std::shared_ptr<Room> a1 = std::make_shared<Room>(1.0f, 1.0f, -3.0f, 3.0f);
        std::shared_ptr<Room> b1 = std::make_shared<Room>(1.0f, 1.0f, -4.0f, -1.0f);
        std::shared_ptr<Room> c1 = std::make_shared<Room>(1.0f, 1.0f, -2.0f, -3.0f);

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
        std::shared_ptr<Room> a1 = std::make_shared<Room>(1.0f, 1.0f, -3.0f, 3.0f);
        std::shared_ptr<Room> b1 = std::make_shared<Room>(1.0f, 1.0f, -4.0f, -1.0f);
        std::shared_ptr<Room> c1 = std::make_shared<Room>(1.0f, 1.0f, -2.0f, -3.0f);

        Edge e1 = Edge(a1, b1);
        Edge e2 = Edge(b1, c1);
        Edge e3 = Edge(c1, a1);

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
