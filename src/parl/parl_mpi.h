/// \file
/// \brief MPI wrapper.
///
/// MPI wrapper functions declaration.

#ifndef CAESAR_PARL_MPI_H
#define CAESAR_PARL_MPI_H

#include "utils/utils.h"

namespace caesar
{

namespace parl
{

/// \addtogroup parl
/// @{

/// \brief MPI requests wrapper.
///
/// MPI requests wrapper.
class MPIRequests
{
    /// \brief Count of requests.
    ///
    /// Count of requests.
    size_t count_ { 0 };

    /// \brief Inner data.
    ///
    /// Inner data for holding specific requests.
    char* data { nullptr };

    // Allocate memory.
    void
    alloc_memory(size_t n);

    // Free memory.
    void
    free_memory();

public:

    // Constructor.
    MPIRequests(size_t n = 0);

    // Copy constructor.
    MPIRequests(const MPIRequests& src);

    // Destructor.
    ~MPIRequests();

    // Get address of request.
    void*
    get(size_t i = 0) const;

    /// \brief Count of requests.
    ///
    /// Count of requests.
    ///
    /// \return
    /// Count of requests.
    inline size_t
    count() const
    {
        return count_;
    }

    // Resize data for requests.
    void
    resize(size_t n);
};

//
// Basic functions.
//

// Check initialization.
bool
is_mpi_initialized();

// Initialization.
int
mpi_init(int* argc,
         char*** argv);

// Finalize.
int
mpi_finalize();

// Barrier.
void
mpi_barrier();

//
// Numbers.
//

// Size.
size_t
mpi_size();

// Rank.
size_t
mpi_rank();

/// \brief Check for zero rank.
///
/// Check for zero rank.
///
/// \return
/// true - if rank of current process is 0,
/// false - otherwise.
inline bool
is_mpi_rank_0()
{
    return mpi_rank() == 0;
}

//
// Data transfer.
//

// Async send.
void
mpi_isend(vector<double>& data,
          size_t process_id,
          MPIRequests& requests,
          size_t request_i);

// Async receive.
void
mpi_irecv(vector<double>& data,
          size_t process_id,
          MPIRequests& requests,
          size_t request_i);

// Wait.
void
mpi_wait(MPIRequests& requests,
         size_t request_i);

// Wait all requests.
void
mpi_waitall(MPIRequests& requests);

// MPI reduce with add operation.
void
mpi_reduce_sum(vector<double>& out_data,
               vector<double>& in_data);

/// @}

}

}

#endif // !CAESAR_PARL_MPI_H
