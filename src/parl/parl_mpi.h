/// \file
/// \brief MPI wrapper.
///
/// MPI wrapper functions declaration.

#ifndef CAESAR_PARL_MPI_H
#define CAESAR_PARL_MPI_H

#include "utils/utils.h"

// Disable cast-function-type warning inside openmpi.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#include "mpi.h"
#pragma GCC diagnostic pop

namespace caesar
{

namespace parl
{

/// \addtogroup parl
/// @{

//
// Basic functions.
//

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
          MPI_Request& request);

// Async receive.
void
mpi_irecv(vector<double>& data,
          size_t process_id,
          MPI_Request& request);

// Wait.
void
mpi_wait(MPI_Request request);

// Wait all requests.
void
mpi_waitall(vector<MPI_Request>& requests);

// MPI reduce with add operation.
void
mpi_reduce_sum(vector<double>& out_data,
               vector<double>& in_data);

/// @}

}

}

#endif // !CAESAR_PARL_MPI_H
