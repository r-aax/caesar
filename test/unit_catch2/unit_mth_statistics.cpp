/// \file
/// \brief Tests for mathematical statistics.
///
/// Tests for mathematical statistics functions.

#include <catch2/catch_test_macros.hpp>
#include "caesar.h"

using namespace caesar;

TEST_CASE("Statistics : statistics functions on vectors", "[mth]")
{
    SECTION("sum & mean")
    {
        vector<double> v { 1.0, 2.0, 3.0, 4.0, 5.0 };

        CHECK(mth::is_near(mth::sum(v), 15.0));
        CHECK(mth::is_near(mth::mean(v), 3.0));
    }
}
