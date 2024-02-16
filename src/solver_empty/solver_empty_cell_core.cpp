/// \file
/// \brief Empty solver cell core implementation.
///
/// \brief Empty solver cell core implementation.

#include "solver_empty_cell_core.h"

namespace solver
{

/// \addtogroup solver
/// @{

/// \brief Default constructor.
CellCore::CellCore()
{
}

/// \brief Default destructor.
CellCore::~CellCore()
{
}

/// \brief Print function.
///
/// Print cell cell to stream.
///
/// \param[in] os Output stream.
/// \param[in] a  Cell core.
ostream&
operator<<(ostream& os,
           const CellCore& v)
{
    os << "cc: htc=" << v.htc << ", beta=" << v.beta;

    return os;
}

/// @}

}
