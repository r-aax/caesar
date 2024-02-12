/// \file
/// \brief Mesh cell declaration.
///
/// Mesh cell declaration.

#ifndef MESH_CELL_H
#define MESH_CELL_H

#include "mesh_edge.h"

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Mesh cell.
class Cell
{
    friend class Zone;

private:

    /// \brief Links to nodes.
    vector<shared_ptr<Node>> nodes;

    /// \brief Links to edges.
    vector<shared_ptr<Edge>> edges;

public:

    // Default constructor.
    Cell();

    // Default destructor.
    ~Cell();
};

/// @}

}

#endif // MESH_CELL_H
