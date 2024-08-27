/// \file
/// \brief Time tests.
///
/// Time tests.

#include <catch2/catch_test_macros.hpp>
#include "utils/utils_time.h"
#include "mth/mth.h"

TEST_CASE("Time : object that can hold time in seconds and microseconds", "[utils]")
{
    SECTION("check all methods")
    {
        utils::Time t05(0.5);
        utils::Time t10(1.0);

        CHECK(mth::is_eq(t05.seconds(), 0.5));
        CHECK(t05.microseconds() == 500000);

        t05.inc_microseconds(500000);

        CHECK(mth::is_eq(t05.seconds(), t10.seconds()));
        CHECK(t05.microseconds() == t10.microseconds());
    }

    SECTION("find time in timestammps")
    {
        CHECK(utils::Time::has_timestamp("x_000111222333"));
        CHECK(!utils::Time::has_timestamp("555"));
        CHECK(!utils::Time::has_timestamp("x_000111y22222"));
        CHECK(!utils::Time::has_timestamp("_000111222222"));
        CHECK(!utils::Time::has_timestamp("x000111222222"));
        CHECK(mth::is_near(utils::Time::get_seconds_from_timestamp("x_000000000000"), 0.0));
        CHECK(mth::is_near(utils::Time::get_seconds_from_timestamp("x_000001000000"), 1.0));
    }
}
