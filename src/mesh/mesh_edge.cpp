/// \file
/// \brief Edge implementation.
///
/// Mesh edge implementation.

#include "mesh_edge.h"
#include "mesh_node.h"
#include "mesh_cell.h"

namespace mesh
{

/// \addtogroup mesh
/// @{

#ifdef DEBUG
// Counter initialization.
int Edge::counter = 0;
#endif // DEBUG

/// \brief Default constructor.
Edge::Edge()
{

#ifdef DEBUG
    ++counter;
#endif // DEBUG

}

/// \brief Default destructor.
Edge::~Edge()
{

#ifdef DEBUG
    --counter;

    if (counter == 0)
    {
        cout << "Last object mesh::Edge is destructed." << endl;
    }
#endif // DEBUG

}

/// \brief Print function.
///
/// Print edge to stream.
///
/// \param[in] os Output stream.
/// \param[in] e  Edge.
ostream&
operator<<(ostream& os,
           const Edge& e)
{
    os << "edge " << e.id << ": " << e.core;

    return os;
}

/// @}

}
