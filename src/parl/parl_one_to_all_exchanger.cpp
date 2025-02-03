/// \file
/// One to all exchanger implementation.
///
/// One to all exchanger implementation.

#include "parl_one_to_all_exchanger.h"

namespace caesar
{

namespace parl
{

/// \addtogroup parl
/// @{

/// \brief Default constructor.
///
/// Default constructor.
OneToAllExchanger::OneToAllExchanger()
{
}

/// \brief Default destructor.
///
/// Default destructor.
OneToAllExchanger::~OneToAllExchanger()
{
}

//
// Allocate memory.
//

/// \brief Allocate buffers.
///
/// Allocate buffers.
void
OneToAllExchanger::allocate()
{
    DEBUG_CHECK_ERROR(buffers.empty(), "there are already buffers allocated");

    size_t r = parl::mpi_rank();
    size_t s = parl::mpi_size();

    if (r == 0)
    {
        // For rank 0 we have to create buffers for all other processes.
        for (size_t i = 1; i < s; ++i)
        {
            buffers.push_back(Buffer(0, i));
        }

        // s - 1 requests.
        requests.resize(s - 1);
    }
    else
    {
        // For other processes we create buffer only with 0.
        buffers.push_back(Buffer(r, 0));

        // Only one request.
        requests.resize(1);
    }
}

/// \brief Set size of exchanges 0 <-> i.
///
/// Set size of buffer.
///
/// \param[in] i           Number of process to 0-th communicate with
/// \param[in] buffer_size Size.
void
OneToAllExchanger::set_size(size_t i,
                            size_t buffer_size)
{
    size_t r = mpi_rank();

    DEBUG_CHECK_ERROR((i > 0) && (i < mpi_size()), "wrong index of buffer");

    if (r == 0)
    {
        buffers[i - 1].set_size(buffer_size);
    }
    else if (r == i)
    {
        buffers[0].set_size(buffer_size);
    }
}

//
// Data transfers.
//

/// \brief Gather data in process 0.
///
/// Gather data in process 0.
void
OneToAllExchanger::gather()
{
    size_t r = mpi_rank();

    if (r == 0)
    {
        for (size_t i = 0; i < buffers.size(); ++i)
        {
            buffers[i].irecv(requests, i);
        }
    }

    mpi_barrier();

    if (r != 0)
    {
        buffers[0].isend(requests, 0);
    }

    mpi_waitall(requests);
}

/// @}

}

}
