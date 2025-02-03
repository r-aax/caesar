/// \file
/// \brief All to all exchanger implementation.
///
/// All to all exchanger implementation.

#include "parl_all_to_all_exchanger.h"

namespace caesar
{

namespace parl
{

/// \addtogroup parl
/// @{

/// \brief Default constructor.
///
/// Default constructor.
AllToAllExchanger::AllToAllExchanger()
{
}

/// \brief Default destructor.
///
/// Default destructor.
AllToAllExchanger::~AllToAllExchanger()
{
}

//
// Allocate memory.
//

/// \brief Allocate buffers.
///
/// Always allocate buffers for all processes.
void
AllToAllExchanger::allocate()
{
    DEBUG_CHECK_ERROR(buffers.empty(), "there are already buffers allocated");

    size_t r = mpi_rank();
    size_t s = mpi_size();

    for (size_t i = 0; i < s; ++i)
    {
        buffers.push_back(Buffer(r, i));

        // Each process communicates with each.
        // isend and irecv for each process.
        requests.resize(2 * s);
    }
}

//
// Data transfer.
//

/// \brief Exchange data.
///
/// Exchange data for all buffers.
/// First we initialize all async exchanges, and then wait all results.
void
AllToAllExchanger::exchange()
{
    size_t s = mpi_size();

    // Init all irecv.
    for (size_t i = 0; i < s; ++i)
    {
        buffers[i].irecv(requests, i);
    }

    mpi_barrier();

    // Init all isend.
    for (size_t i = 0; i < s; ++i)
    {
        buffers[i].isend(requests, s + i);
    }

    mpi_waitall(requests);
}

/// @}

}

}
