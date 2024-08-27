/// \file
/// \brief Utils system tests.
///
/// Utils system tests.

#include <catch2/catch_test_macros.hpp>
#include "utils/utils_system.h"

TEST_CASE("system : some system features", "[utils]")
{
    SECTION("hash functions")
    {
        double a = -4.34632784626478;
        double b = -4.34632784626478;
        double c = 12.32423423432432;

        CHECK(utils::double_hash(a) == utils::double_hash(b));
        CHECK(utils::double_hash(b) != utils::double_hash(c));
        CHECK(utils::double_hash(a) != utils::double_hash(c));
    }
}
