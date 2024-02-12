/// \file
/// \brief Empty solver edge atom implementation.
///
/// \brief Empty solver edg atom implementation.

#include "solver_empty_edge_atom.h"

namespace solver
{

/// \addtogroup solver
/// @{

/// \brief Default constructor.
EdgeAtom::EdgeAtom()
{
}

/// \brief Default destructor.
EdgeAtom::~EdgeAtom()
{
}

/// \brief Print function.
///
/// Print edge atom to stream.
///
/// \param[in] os Output stream.
/// \param[in] a  Node atom.
ostream&
operator<<(ostream& os,
           const EdgeAtom& v)
{
    os << "ea:";

    return os;
}

/// @}

}
