#include "dungeon_generation/data/Array.h"

#include "doctest.h"
#include <sstream>

TEST_SUITE("Test Array")
{
    TEST_CASE("Test Add")
    {
        Array<std::string> arr;
        arr.Add("test1", "test5", "yes", "", "no");
        CHECK(arr.Size() == 5);
        CHECK(arr[0] == "test1");
        CHECK(arr[1] == "test5");
        CHECK(arr[2] == "yes");
        CHECK(arr[3] == "");

        std::string str = arr[4];
        CHECK(str == "no");
    }

    TEST_CASE("Test copy assignment and constructor")
    {
        Array<float> arr;
        arr.Add(4.2f, 0.0f, 3.2f, -9.321f);

        Array<float> arr2;
        arr2 = arr;

        Array<float> arr3(arr);
        
        CHECK(arr.Size() == arr2.Size());
        CHECK(arr.Size() == arr3.Size());

        for (int i = 0; i < arr.Size(); i++)
        {
            CHECK(arr[i] == arr2[i]);
            CHECK(arr[i] == arr3[i]);
        }
    }

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
        arr.Add(-2);
        arr.Add(-4);
        arr.Add(7);
        arr.Add(8);
        arr.Add(9);
        arr.Add(6);
        arr.Add(0);
        arr.Add(95);

        arr.Sort([](const int& a, const int& b) { return b - a; });

        int sorted[] =  {-4, -2, 0, 1, 3, 5, 6, 7, 8, 9, 95};
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
        CHECK_THROWS(arr.Remove(3));

        arr.Unlock();
        CHECK_NOTHROW(arr.Add(2));
        CHECK_NOTHROW(arr.Sort([](const int& a, const int& b) { return b - a; }));
        CHECK_NOTHROW(arr = arr2);
        CHECK_NOTHROW(arr = Array<int>());
        CHECK_NOTHROW(arr.Remove(3));
    }

    TEST_CASE("Test remove")
    {
        Array<int> arr;
        arr.Add(5, 5, 6, 9, 21, 31, 0);
        
        arr.Remove(5);
        CHECK(arr.Size() == 6);
        arr.Remove(0);
        CHECK(arr.Size() == 5);
        CHECK(arr[2] == 9);
        arr.Add(2);
        CHECK(arr.Size() == 6);
        arr.Remove(21);
        CHECK(arr.Size() == 5);
        CHECK(arr[4] == 2);
    }

    TEST_CASE("Test string stream operators")
    {
        Array<int> arr;
        arr.Add(5, 5, 6, -9, 21, 31, 0);

        Array<std::shared_ptr<int>> arrPtr;
        arrPtr.Add(std::make_shared<int>(65), std::make_shared<int>(65), std::make_shared<int>(6000000), std::make_shared<int>(-12));
        std::stringstream ss;
        ss << arr;

        CHECK(ss.str() == "[5, 5, 6, -9, 21, 31, 0]");
        ss.str("");
        ss << arrPtr;
        CHECK(ss.str() == "[65, 65, 6000000, -12]");
    }
}
