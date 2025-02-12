/// \file
/// \brief Tests for mathematical basic function.
///
/// Tests for mathematical basic functions.

#include <catch2/catch_test_macros.hpp>
#include "caesar.h"

using namespace caesar;

TEST_CASE("Basics : basic functions", "[mth]")
{
    SECTION("convert angles")
    {
        // degrees to radians
        CHECK(mth::is_near(mth::degrees_to_radians(0.0), 0.0));
        CHECK(mth::is_near(mth::degrees_to_radians(45.0), mth::Pi / 4.0));
        CHECK(mth::is_near(mth::degrees_to_radians(90.0), mth::Pi / 2.0));
        CHECK(mth::is_near(mth::degrees_to_radians(180.0), mth::Pi));

        // radians to degrees
        CHECK(mth::is_near(mth::radians_to_degrees(0.0), 0.0));
        CHECK(mth::is_near(mth::radians_to_degrees(mth::Pi / 4.0), 45.0));
        CHECK(mth::is_near(mth::radians_to_degrees(mth::Pi / 2.0), 90.0));
        CHECK(mth::is_near(mth::radians_to_degrees(mth::Pi), 180.0));
    }

    SECTION("weighted sum")
    {
        CHECK(mth::is_near(mth::weighted_sum(1.0, 10.0, 20.0), 15.0));
        CHECK(mth::is_near(mth::weighted_sum(9.0, 1.0, 11.0), 2.0));
    }
}
