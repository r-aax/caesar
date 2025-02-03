/// \file
/// \brief MPI tests.
///
/// MPI tests.

#include <catch2/catch_test_macros.hpp>
#include "caesar.h"

using namespace caesar;

TEST_CASE("MPI : mpi functions", "[parl]")
{
    SECTION("using MPIRequests")
    {
        parl::MPIRequests reqs, reqs2(2);

        // Check size before and after resize.
        CHECK(reqs.count() == 0);
        CHECK(reqs2.count() == 2);
        reqs.resize(5);
        reqs2.resize(10);
        CHECK(reqs.count() == 5);
        CHECK(reqs2.count() == 10);
    }

    SECTION("using mpi before initialization")
    {
        // Barrier has no return type.
        parl::mpi_barrier();

        // Without initilization there is only one process with rank 0.
        CHECK(parl::mpi_rank() == 0);
        CHECK(parl::mpi_size() == 1);

        // Without initilization there is no exchanges.
        vector<double> data;
        parl::MPIRequests requests(2);
        parl::mpi_isend(data, 0, requests, 0);
        parl::mpi_irecv(data, 0, requests, 1);
        parl::mpi_wait(requests, 0);
        parl::mpi_waitall(requests);
        parl::mpi_reduce_sum(data, data);
    }
}
