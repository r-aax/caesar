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

class Cell;

/// \brief Mesh edge.
class Edge
{

private:

    /// \brief Identifier.
    int id { -1 };

    /// \brief Links to nodes.
    vector<shared_ptr<Node>> nodes;

    /// \brief Links to cells.
    vector<shared_ptr<Cell>> cells;

public:

#ifdef DEBUG
    static int counter;
#endif // DEBUG

    // Default constructor.
    Edge();

    // Default destructor.
    virtual
    ~Edge();

    // Print function.
    friend ostream&
    operator<<(ostream& os,
               const Edge& e);
};

/// @}

}

#endif // MESH_EDGE_H
