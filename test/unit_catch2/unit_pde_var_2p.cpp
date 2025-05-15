/// \file
/// \brief Tests for PDE Var2P.
///
/// Tests for PDE Var2P.

#include <catch2/catch_test_macros.hpp>
#include "caesar.h"

using namespace caesar;

TEST_CASE("PDE : Var2P", "[pde]")
{
    SECTION("common operations")
    {
        pde::Var2P v, w;

        CHECK(mth::is_zero(v.get()));
        CHECK(mth::is_zero(v.diff()));

        v.set(1.0);

        CHECK(mth::is_eq(v.get(), 1.0));
        CHECK(v.diff() > 0.0);

        v.back();

        CHECK(mth::is_zero(v.diff()));

        v.set(2.0);
        w.set(3.0);

        CHECK(mth::is_eq(pde::Var2P::mul_diff(v, w), 6.0));

        w.set_both(5.0);

        CHECK(mth::is_zero(w.diff()));
    }
}
