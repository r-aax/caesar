/// \file
/// \brief MPI tests.
///
/// MPI tests.

#include <catch2/catch_test_macros.hpp>
#include "caesar.h"

using namespace caesar;

TEST_CASE("MPI : mpi functions", "[parl]")
{
    SECTION("using mpi before initialization")
    {
        CHECK(parl::mpi_rank() == 0);
        CHECK(parl::mpi_size() == 1);
    }
}
