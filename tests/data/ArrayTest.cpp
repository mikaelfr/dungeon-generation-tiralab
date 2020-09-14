#include "dungeon_generation/data/Array.h"

#include "doctest.h"

TEST_SUITE("Test Array")
{
    TEST_CASE("Test Size")
    {
        Array<int> arr;
        for (int i = 0; i < 10; i++)
        {
            arr.Add(i);
        }

        CHECK(arr.Size() == 10);
    }

    TEST_CASE("Test Sort")
    {
        Array<int> arr;
        arr.Add(5);
        arr.Add(3);
        arr.Add(1);
        arr.Add(2);
        arr.Add(4);
        arr.Add(7);
        arr.Add(8);
        arr.Add(9);
        arr.Add(6);
        arr.Add(0);
        arr.Add(95);

        arr.Sort([](const int& a, const int& b) { return b - a; });

        int sorted[] =  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 95};
        for (int i = 0; i < arr.Size(); i++)
        {
            CHECK(arr[i] == sorted[i]);
        }
    }

    TEST_CASE("Test locking")
    {
        Array<int> arr;
        arr.Add(5);
        arr.Add(3);
        arr.Add(1);

        arr.Lock();

        Array<int> arr2;
        CHECK_THROWS(arr = arr2);
        CHECK_THROWS(arr = Array<int>());
        CHECK_THROWS(arr.Add(2));
        CHECK_THROWS(arr.Sort([](const int& a, const int& b) { return b - a; }));

        arr.Unlock();
        CHECK_NOTHROW(arr.Add(2));
        CHECK_NOTHROW(arr.Sort([](const int& a, const int& b) { return b - a; }));
        CHECK_NOTHROW(arr = arr2);
        CHECK_NOTHROW(arr = Array<int>());
    }
}
