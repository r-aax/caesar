/// \file
/// \brief Cell implementation.
///
/// Mesh cell implementation.

#include "mesh_cell.h"

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Default constructor.
Cell::Cell()
{
}

/// \brief Default destructor.
Cell::~Cell()
{
}

/// \brief Print function.
///
/// Print cell to stream.
///
/// \param[in] os Output stream.
/// \param[in] c  Cell.
ostream&
operator<<(ostream& os,
           const Cell& c)
{
    os << "cell: " << c.atom;

    return os;
}

/// @}

}
