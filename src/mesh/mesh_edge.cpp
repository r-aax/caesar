/// \file
/// \brief Edge implementation.
///
/// Mesh edge implementation.

#include "mesh_edge.h"

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Default constructor.
Edge::Edge()
{
}

/// \brief Default destructor.
Edge::~Edge()
{
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
    os << "edge: " << e.atom;

    return os;
}

/// @}

}
