/// \file
/// \brief Empty solver node core implementation.
///
/// \brief Empty solver node core implementation.

#include "solver_empty_node_core.h"

namespace solver
{

/// \addtogroup solver
/// @{

/// \brief Default constructor.
NodeCore::NodeCore()
{
}

/// \brief Default destructor.
NodeCore::~NodeCore()
{
}

/// \brief Print function.
///
/// Print node cell to stream.
///
/// \param[in] os Output stream.
/// \param[in] a  Node core.
ostream&
operator<<(ostream& os,
           const NodeCore& v)
{
    os << "nc:";

    return os;
}

/// @}

}
