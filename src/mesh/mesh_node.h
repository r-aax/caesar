/// \file
/// \brief Mesh node declaration.
///
/// Mesh node declaration.

#ifndef MESH_NODE_H
#define MESH_NODE_H

#include "geom/geom.h"

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Mesh node.
class Node
{

private:

    /// \brief Vector (point).
    geom::Vector point;

public:

    // Default constructor.
    Node();

    // Constructor by point coordinates.
    Node(double x,
         double y,
         double z);

    // Default destructor.
    ~Node();
};

/// @}

}

#endif // MESH_NODE_H
