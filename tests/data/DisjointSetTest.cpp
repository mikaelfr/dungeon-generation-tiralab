#include "dungeon_generation/data/DisjointSet.h"

#include "doctest.h"

TEST_SUITE("Test DisjointSet")
{
    TEST_CASE("Test Equality")
    {
        DisjointSet<int> set1(90);
        DisjointSet<int> set2(-89);
        DisjointSet<int> set3(0);
        DisjointSet<int> set4(1);

        CHECK(set1 == set1);
        CHECK(set2 == set2);
        CHECK(set3 == set3);
        CHECK(set4 == set4);

        CHECK(set1 != set2);
        CHECK(set2 != set1);
        CHECK(set3 != set4);
        CHECK(set4 != set3);
    }

    TEST_CASE("Test Find and Union")
    {
        DisjointSet<int> set1(90);
        DisjointSet<int> set2(-89);
        DisjointSet<int> set3(0);
        DisjointSet<int> set4(1);

        CHECK(*set1.Find() == set1);
        CHECK(*set2.Find() == set2);
        CHECK(*set3.Find() == set3);
        CHECK(*set4.Find() == set4);

        set1 += set2;
        set3 += set4;

        CHECK(*set1.Find() == set1);
        CHECK(*set2.Find() == set1);
        CHECK(*set3.Find() == set3);
        CHECK(*set4.Find() == set3);
        
        set1 += set3;

        CHECK(*set1.Find() == set1);
        CHECK(*set2.Find() == set1);
        CHECK(*set3.Find() == set1);
        CHECK(*set4.Find() == set1);
    }
}
