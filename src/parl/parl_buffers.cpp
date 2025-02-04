/// \file
/// \brief Buffers implementation.
///
/// Buffers implementation.

#include "parl_buffers.h"

namespace caesar
{

namespace parl
{

/// \addtogroup parl
/// @{

/// \brief Default constructor.
///
/// Default constructor.
Buffers::Buffers()
{
}

/// \brief Default destructor.
///
/// Default destructor.
Buffers::~Buffers()
{
}

//
// Print information.
//

/// \brief Print.
///
/// Print information.
///
/// \param[out] os Out stream.
void
Buffers::print(ostream& os)
{
    size_t bc { buffers.size() };

    os << "Buffers (rank = " << mpi_rank() << "):" << endl;

    for (size_t i = 0; i < bc; ++i)
    {
        buffers[i].print(os);
    }
}

/// \brief Print all.
///
/// Print information for all processes.
///
/// \param[out] os Out stream.
void
Buffers::print_all(ostream& os)
{
    size_t s = mpi_size();

    for (size_t i = 0; i < s; ++i)
    {
        if (mpi_rank() == i)
        {
            print(os);
        }

        mpi_barrier();
    }
}

/// @}

}

}
