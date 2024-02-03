#include <catch2/catch_test_macros.hpp>
#include <FMaths/Vector3.h>

TEST_CASE("Accessing Variables", "[Vector3]")
{
    Vector3 vec(1.f, 2.f, 3.f);

    REQUIRE(vec.X == ((float*)&vec)[0]);
    REQUIRE(vec.Y == ((float*)&vec)[1]);
    REQUIRE(vec.Z == ((float*)&vec)[2]);
}