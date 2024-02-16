/// \file
/// \brief Timer tests.
///
/// Timer tests.

#include "utils/utils.h"
#include <catch2/catch.hpp>

TEST_CASE("timer : multiple measure the time", "[utils]")
{
    SECTION("check all methods")
    {
        utils::Timer t;

        CHECK(t.get() == 0.0);

        t.start();
        double a = t.get();
        t.stop();
        t.start();
        double b = t.get();

        CHECK(b >= a);
    }
}
