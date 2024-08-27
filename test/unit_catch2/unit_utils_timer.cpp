/// \file
/// \brief Timer tests.
///
/// Timer tests.

#include <catch2/catch_test_macros.hpp>
#include "utils/utils_timer.h"
#include "mth/mth.h"

TEST_CASE("Timer : multiple measure the time", "[utils]")
{
    SECTION("check all methods")
    {
        utils::Timer t;

        CHECK(mth::is_zero(t.get()));

        t.start();
        double a = t.get();
        t.stop();
        t.start();
        double b = t.get();

        CHECK(b >= a);
    }
}
