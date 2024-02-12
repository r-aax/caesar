/// \file
/// \brief Empty solver node atom implementation.
///
/// \brief Empty solver node atom implementation.

#include "solver_empty_node_atom.h"

namespace solver
{

/// \addtogroup solver
/// @{

/// \brief Default constructor.
NodeAtom::NodeAtom()
{
}

/// \brief Default destructor.
NodeAtom::~NodeAtom()
{
}

/// \brief Print function.
///
/// Print node atom to stream.
///
/// \param[in] os Output stream.
/// \param[in] a  Node atom.
ostream&
operator<<(ostream& os,
           const NodeAtom& v)
{
    os << "na:";

    return os;
}

/// @}

}
