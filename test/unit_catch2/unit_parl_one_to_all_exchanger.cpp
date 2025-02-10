/// \file
/// \brief Tests for one to all exchanger.
///
/// Parl one to all exchanger tests.

#include <catch2/catch_test_macros.hpp>
#include "caesar.h"

using namespace caesar;

TEST_CASE("One to all exchanger : one process to all other proceccess", "[parl]")
{
    SECTION("create and release")
    {
        parl::OneToAllExchanger ex;

        ex.allocate();
    }
}
