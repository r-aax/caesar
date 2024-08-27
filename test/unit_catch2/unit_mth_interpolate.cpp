/// \file
/// \brief Tests for interpolation function.
///
/// Tests for mathematical interpolation functions.

#include <catch2/catch_test_macros.hpp>
#include "caesar.h"

using namespace caesar;

TEST_CASE("Interpolate : interpolation of 1D function", "[mth]")
{
    SECTION("hard stair")
    {
        double xlo = -1.0, xhi = 3.0, ylo = -2.0, yhi = 2.0;

        CHECK(mth::is_near(mth::hard_stair(-2.0, xlo, xhi, ylo, yhi), ylo));
        CHECK(mth::is_near(mth::hard_stair(-1.0, xlo, xhi, ylo, yhi), ylo));
        CHECK(mth::is_near(mth::hard_stair(0.0, xlo, xhi, ylo, yhi), -1.0));
        CHECK(mth::is_near(mth::hard_stair(2.0, xlo, xhi, ylo, yhi), 1.0));
        CHECK(mth::is_near(mth::hard_stair(3.0, xlo, xhi, ylo, yhi), yhi));
        CHECK(mth::is_near(mth::hard_stair(4.0, xlo, xhi, ylo, yhi), yhi));
    }
}
