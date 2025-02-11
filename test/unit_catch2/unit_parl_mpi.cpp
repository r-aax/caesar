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

    SECTION("MPIRequests copy constructor")
    {
        // issue #47

        parl::MPIRequests reqs(5);
        parl::MPIRequests copy = reqs;

        CHECK(reqs.count() == 5);
        CHECK(copy.count() == 5);
    }

    SECTION("MPIRequests copy constructor for zero-size requests")
    {
        // issue #47

        parl::MPIRequests reqs(0);
        parl::MPIRequests copy = reqs;

        CHECK(reqs.count() == 0);
        CHECK(copy.count() == 0);
    }

    SECTION("MPIRequests copy constructor for different sizes")
    {
        // issue #47

        vector<parl::MPIRequests> v
        {
            parl::MPIRequests(0), parl::MPIRequests(1), parl::MPIRequests(2)
        };

        CHECK(v[0].count() == 0);
        CHECK(v[1].count() == 1);
        CHECK(v[2].count() == 2);
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
