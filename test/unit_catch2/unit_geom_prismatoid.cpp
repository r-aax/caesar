/// \file
/// \brief Tests for prismatoids.
///
/// Tests for prismatoids.

#include <catch2/catch_test_macros.hpp>
#include "geom/geom_prismatoid.h"
#include "mth/mth.h"

TEST_CASE("Prismatoid", "[geom]")
{
    SECTION("prismatoid volume coefficients")
    {
        geom::Vector v1(0.0, 0.0, 0.0), v2(1.0, 0.0, 0.0), v3(0.0, 1.0, 0.0);
        geom::Vector n1(0.0, 0.0, 1.0), n2(0.0, 0.0, 1.0), n3(0.0, 0.0, 1.0);
        geom::Vector n(0.0, 0.0, 1.0);
        double a, b, c;

        geom::prismatoid_volume_coefficients(v1, v2, v3, n1, n2, n3, n, a, b, c);

        CHECK(mth::is_eq(a, 0.5));
        CHECK(mth::is_eq(b, 0.0));
        CHECK(mth::is_eq(c, 0.0));
    }
}
