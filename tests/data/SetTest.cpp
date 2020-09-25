#include "dungeon_generation/data/Set.h"

#include "doctest.h"

TEST_SUITE("Test Set")
{
    TEST_CASE("Test Add")
    {
        Set<int> set;
        set.Add(1, 2, 3, 3, 8, 9, 10, 2, 1, 5);

        int referenceArr[]{ 1, 2, 3, 8, 9, 10, 5 };
        int referenceArrLen = sizeof(referenceArr) / sizeof(referenceArr[0]);

        CHECK(set.Size() == referenceArrLen);

        for (int i = 0; i < set.Size(); i++)
        {
            CHECK(set[i] == referenceArr[i]);
        }
    }
}
