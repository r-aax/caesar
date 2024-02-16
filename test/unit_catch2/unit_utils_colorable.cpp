/// \file
/// \brief Colorable object tests.
///
/// Colorable object tests.

#include "utils/utils.h"
#include <catch2/catch.hpp>

TEST_CASE("colorable : object that can be colored", "[utils]")
{
    SECTION("check all methods")
    {
        utils::Colorable obj;

        int c = obj.first_free_color();

        CHECK(c == 0);

        obj.paint(0);
        obj.paint(1);
        obj.paint(2);
        c = obj.first_free_color();

        CHECK(c == 3);

        obj.clear(1);
        c = obj.first_free_color();

        CHECK(c == 1);
    }
}
