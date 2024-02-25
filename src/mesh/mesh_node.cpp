/// \file
/// \brief Node implementation.
///
/// Mesh node implementation.

#include "mesh_node.h"
#include "mesh_edge.h"
#include "mesh_cell.h"

namespace mesh
{

/// \addtogroup mesh
/// @{

#ifdef DEBUG
// Counter initialization.
int Node::counter = 0;
#endif // DEBUG

/// \brief Default constructor.
Node::Node()
    : point()
{

#ifdef DEBUG
    ++counter;
#endif // DEBUG

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

#ifdef DEBUG
    ++counter;
#endif // DEBUG

}

/// \brief Default destructor.
Node::~Node()
{

#ifdef DEBUG
    --counter;

    if (counter == 0)
    {
        cout << "Last object mesh::Node is destructed." << endl;
    }
#endif // DEBUG

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
    os << "node " << n.id;

    return os;
}

/// @}

}
