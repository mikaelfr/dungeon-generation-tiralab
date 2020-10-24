#include "dungeon_generation/data/Tuple.h"

#include "doctest.h"
#include <sstream>

TEST_SUITE("Test Triangle")
{
    TEST_CASE("Test constructors")
    {
        Tuple<int, std::string> tuple1;
        Tuple<int, std::string> tuple2(3, "test");

        CHECK(tuple1.key == 0);
        CHECK(tuple1.value == std::string());
        CHECK(tuple2.key == 3);
        CHECK(tuple2.value == "test");

        tuple1.key = 2;
        tuple1.value = "yes";

        CHECK(tuple1.key == 2);
        CHECK(tuple1.value == "yes");
    }

    TEST_CASE("Test stream operator")
    {
        Tuple<int, std::string> tuple(3, "test");
        std::stringstream ss;
        ss << tuple;
        CHECK(ss.str() == "{\"start\": 3, \"end\": test}");
    }
}
