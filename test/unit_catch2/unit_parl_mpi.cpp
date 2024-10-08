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
        // Barrier has no return type.
        parl::mpi_barrier();

        // Without initilization there is only one process with rank 0.
        CHECK(parl::mpi_rank() == 0);
        CHECK(parl::mpi_size() == 1);

        // Without initilization there is no exchanges.
        vector<double> data;
        MPI_Request request1, request2;
        vector<MPI_Request> requests { request1, request2 };
        parl::mpi_isend(data, 0, request1);
        parl::mpi_irecv(data, 0, request2);
        parl::mpi_wait(request1);
        parl::mpi_waitall(requests);
        parl::mpi_reduce_sum(data, data);
    }
}
