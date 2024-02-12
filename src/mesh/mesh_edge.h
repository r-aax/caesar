/// \file
/// \brief Mesh edge declaration.
///
/// Mesh edge declaration.

#ifndef MESH_EDGE_H
#define MESH_EDGE_H

#include "mesh_node.h"

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Mesh edge.
class Edge
{

private:

    /// \brief Links to nodes.
    vector<shared_ptr<Node>> nodes;

    /// \brief Links to cells.
    vector<shared_ptr<Edge>> edges;

public:

    // Default constructor.
    Edge();

    // Default destructor.
    ~Edge();
};

/// @}

}

#endif // MESH_EDGE_H
