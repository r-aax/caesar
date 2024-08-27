/// \file
/// \brief Tests for mathematical functions for bits manipulation.
///
/// Tests for mathematical functions for bits manipulations.

#include <catch2/catch_test_macros.hpp>
#include "caesar.h"

using namespace caesar;

TEST_CASE("Bits : bits manipulation functions", "[mth]")
{
    SECTION("least bits")
    {
        // 0
        CHECK(mth::least_bit_0(0) == 0);
        CHECK(mth::least_bit_1(0) == -1);

        // 0110
        CHECK(mth::least_bit_0(6) == 0);
        CHECK(mth::least_bit_1(6) == 1);

        // 1000 0111
        CHECK(mth::least_bit_0(135) == 3);
        CHECK(mth::least_bit_1(135) == 0);

        // 0110 0011 0000 0000
        CHECK(mth::least_bit_0(0x6300) == 0);
        CHECK(mth::least_bit_1(0x6300) == 8);

        // 1000 0101 1111 1111 1111 1111
        CHECK(mth::least_bit_0(0x85FFFF) == 17);
        CHECK(mth::least_bit_1(0x85FFFF) == 0);

        // 1111 1111 1111 1111 1111 1111 1111 1111
        CHECK(mth::least_bit_0(0xFFFFFFFF) == -1);
        CHECK(mth::least_bit_1(0xFFFFFFFF) == 0);
    }
}
