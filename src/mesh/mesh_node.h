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

    /// \brief Identifier.
    int id { -1 };

    /// \brief Vector (point).
    geom::Vector point;

    /// \brief Links to edges.
    vector<shared_ptr<Edge>> edges;

    /// \brief Links to cells.
    vector<shared_ptr<Cell>> cells;

    /// \brief Mark.
    int mark;

public:

#ifdef DEBUG
    static int counter;
#endif // DEBUG

    // Default constructor.
    Node();

    // Constructor by point coordinates.
    Node(double x,
         double y,
         double z);

    // Default destructor.
    virtual
    ~Node();

    // Print function.
    friend ostream&
    operator<<(ostream& os,
               const Node& n);
};

/// @}

}

#endif // MESH_NODE_H
