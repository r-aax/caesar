/// \file
/// \brief Empty solver cell atom implementation.
///
/// \brief Empty solver cell atom implementation.

#include "solver_empty_cell_atom.h"

namespace solver
{

/// \addtogroup solver
/// @{

/// \brief Default constructor.
CellAtom::CellAtom()
{
}

/// \brief Default destructor.
CellAtom::~CellAtom()
{
}

/// \brief Print function.
///
/// Print cell atom to stream.
///
/// \param[in] os Output stream.
/// \param[in] a Cell atom.
ostream&
operator<<(ostream& os,
           const CellAtom& v)
{
    os << "ca:";

    return os;
}

/// @}

}
