#include <catch2/catch_test_macros.hpp>
#include <FMaths/Matrix4x4.h>

TEST_CASE("Accessing variables", "[Matrix4x4]")
{
    Matrix4x4 mat(1.f);

    REQUIRE(((float*)&mat)[0] == 1.f);
    REQUIRE(((float*)&mat)[5] == 1.f);
    REQUIRE(((float*)&mat)[10] == 1.f);
    REQUIRE(((float*)&mat)[15] == 1.f);
}