/// \file
/// \brief Node implementation.
///
/// Mesh node implementation.

#include "mesh_node.h"

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Default constructor.
Node::Node()
    : point()
{
}

/// \brief Constructor by point coordinates.
///
/// \param[in] x Point coordinate X.
/// \param[in] y Point coordinate Y.
/// \param[in] z Point coordinate Z.
Node::Node(double x,
           double y,
           double z)
    : point(x, y, z)
{
}

/// \brief Default destructor.
Node::~Node()
{
}

/// @}

}
