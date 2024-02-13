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

/// \brief Print function.
///
/// Print node to stream.
///
/// \param[in] os Output stream.
/// \param[in] n  Node.
ostream&
operator<<(ostream& os,
           const Node& n)
{
    os << "node " << n.id << ": " << n.atom;

    return os;
}

/// @}

}
