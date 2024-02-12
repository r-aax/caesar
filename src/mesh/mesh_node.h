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

class Edge;
class Cell;

/// \brief Mesh node.
class Node
{
    friend class Zone;

private:

    /// \brief Vector (point).
    geom::Vector point;

    /// \brief Links to edges.
    vector<shared_ptr<Edge>> edges;

    /// \brief Links to cells.
    vector<shared_ptr<Cell>> cells;

    /// \brief Mark.
    int mark;

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
