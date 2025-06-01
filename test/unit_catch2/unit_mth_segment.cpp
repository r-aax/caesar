/// \file
/// \brief Tests for mathematical functions for interval.
///
/// Tests for mathematical functions for interval.

#include <catch2/catch_test_macros.hpp>
#include "caesar.h"

using namespace caesar;

TEST_CASE("Segment : segment functions", "[mth]")
{
    SECTION("main fucntions")
    {
        mth::Segment s1;

        // Default segment.
        CHECK(s1.is_real());
        CHECK(mth::is_near(s1.len(), 0.0));

        // Given segment.
        mth::Segment s2(-5.0, 10.0);
        CHECK(mth::is_near(s2.len(), 15.0));

        // Around point segment and non_neg, non_pos parts.
        mth::Segment s3 { mth::Segment::around_point(2.0, 10.0) };
        mth::Segment s4 { s3.non_neg() };
        mth::Segment s5 { s3.non_pos() };
        CHECK(mth::is_near(s4.len(), 12.0));
        CHECK(mth::is_near(s5.len(), 8.0));

        // Contains points check.
        CHECK(s3.contains(0.0));
        CHECK(!s3.contains(100.0));
    }
}
