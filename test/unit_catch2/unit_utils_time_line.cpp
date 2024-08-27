/// \file
/// \brief Time line tests.
///
/// Time line tests.

#include <catch2/catch_test_macros.hpp>
#include "caesar.h"

using namespace caesar;

TEST_CASE("TimeLine : ", "[utils]")
{
    SECTION("check all methods")
    {
        utils::TimeLine tl(0.0, 10.0, 5.0);
        utils::Time t(2.0);

        CHECK(!tl.is_finished());
        CHECK(tl.iteration() == 0);

        tl.next_iteration();

        CHECK(!tl.is_time_multiple(t));
        CHECK(tl.iteration() == 1);

        tl.next_iteration();

        CHECK(tl.is_finished());
        CHECK(tl.is_time_multiple(t));
    }
}
