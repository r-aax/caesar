/// \file
/// \brief Tests for mathematical functions for interval.
///
/// Tests for mathematical functions for interval.

#include <catch2/catch_test_macros.hpp>
#include "caesar.h"

using namespace caesar;

TEST_CASE("Interval : interval functions", "[mth]")
{
    SECTION("main fucntions")
    {
        mth::Interval i1;

        // Default interval.
        CHECK(i1.is_real());
        CHECK(mth::is_near(i1.len(), 0.0));

        // Given interval.
        mth::Interval i2(-5.0, 10.0);
        CHECK(mth::is_near(i2.len(), 15.0));

        // Around point interval and non_neg, non_pos parts.
        mth::Interval i3 { mth::Interval::around_point(2.0, 10.0) };
        mth::Interval i4 { i3.non_neg() };
        mth::Interval i5 { i3.non_pos() };
        CHECK(mth::is_near(i4.len(), 12.0));
        CHECK(mth::is_near(i5.len(), 8.0));
    }
}
