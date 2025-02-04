/// \file
/// \brief Boundaries between domains.
///
/// Boundary between domains implementation.

#include "mesh_boundaries.h"

#include "parl/parl.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Default constructor.
///
/// Default constructor.
Boundaries::Boundaries()
{
}

/// \brief Default destructor.
///
/// Default destructor.
Boundaries::~Boundaries()
{
}

/// \brief Allocate boundaries.
///
/// Allocate as many boundaries as we have processes.
void
Boundaries::allocate()
{
    DEBUG_CHECK_ERROR(boundaries.empty(), "there are already boundaries allocated");

    // We have to hold boundary for each process (including the current one).
    size_t r = parl::mpi_rank();
    size_t s = parl::mpi_size();

    for (size_t i = 0; i < s; ++i)
    {
        boundaries.push_back(Boundary(r, i));
    }

    // Allocate communicator.
    comm.allocate();
}

/// \brief Print in current process.
///
/// Print in current process.
///
/// \param[out] os Out stream.
void
Boundaries::print(ostream& os)
{
    os << "Boundaries (rank = " << parl::mpi_rank() << "):" << endl;

    for (size_t i = 0; i < boundaries.size(); ++i)
    {
        boundaries[i].print(os);
    }
}

/// \brief Print in all processes.
///
/// Print in all processes.
///
/// \param[out] os Out stream.
void
Boundaries::print_all(ostream& os)
{
    size_t s = parl::mpi_size();

    for (size_t i = 0; i < s; ++i)
    {
        if (parl::mpi_rank() == i)
        {
            print(os);
        }

        parl::mpi_barrier();
    }

    comm.print_all();
}

/// \brief Set buffers sizes.
///
/// Set buffer sizes from boundaries.
void
Boundaries::set_buffers_sizes()
{
    size_t s = boundaries.size();

    for (size_t i = 0; i < s; ++i)
    {
        comm.set_size(i, boundaries[i].size());
    }
}

/// \brief Exchange.
///
/// Exchange data inside superbuffer.
void
Boundaries::exchange()
{
    comm.exchange();
}

/// @}

}

}
