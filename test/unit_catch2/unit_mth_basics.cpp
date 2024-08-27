/// \file
/// \brief Tests for mathematical basic function.
///
/// Tests for mathematical basic functions.

#include <catch2/catch_test_macros.hpp>
#include "mth/mth_basics.h"

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
}
