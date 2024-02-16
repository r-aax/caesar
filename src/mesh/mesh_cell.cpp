/// \file
/// \brief Cell implementation.
///
/// Mesh cell implementation.

#include "mesh_cell.h"
#include "mesh_node.h"
#include "mesh_edge.h"

namespace mesh
{

/// \addtogroup mesh
/// @{

#ifdef DEBUG
// Counter initialization.
int Cell::counter = 0;
#endif // DEBUG

/// \brief Default constructor.
Cell::Cell()
{

#ifdef DEBUG
    ++counter;
#endif // DEBUG

}

/// \brief Default destructor.
Cell::~Cell()
{

#ifdef DEBUG
    --counter;

    if (counter == 0)
    {
        cout << "Last object mesh::Cell is destructed." << endl;
    }
#endif // DEBUG

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
    os << "cell " << c.id << ": " << *((solver::CellCore*)&c);

    return os;
}

/// @}

}
