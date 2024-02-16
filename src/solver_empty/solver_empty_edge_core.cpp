/// \file
/// \brief Empty solver edge core implementation.
///
/// \brief Empty solver edge core implementation.

#include "solver_empty_edge_core.h"

namespace solver
{

/// \addtogroup solver
/// @{

/// \brief Default constructor.
EdgeCore::EdgeCore()
{
}

/// \brief Default destructor.
EdgeCore::~EdgeCore()
{
}

/// \brief Print function.
///
/// Print edge cell to stream.
///
/// \param[in] os Output stream.
/// \param[in] a  Edge core.
ostream&
operator<<(ostream& os,
           const EdgeCore& v)
{
    os << "ec:";

    return os;
}

/// @}

}
