/// \file
/// \brief Mesh edge declaration.
///
/// Mesh edge declaration.

#ifndef MESH_EDGE_H
#define MESH_EDGE_H

#include "mesh_node.h"
#include "solver/solver.h"

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Mesh edge.
class Edge
{

private:

    /// \brief Identifier.
    int id { -1 };

    /// \brief Links to nodes.
    vector<shared_ptr<Node>> nodes;

    /// \brief Links to cells.
    vector<shared_ptr<Edge>> edges;

    /// \brief Edge atom.
    solver::EdgeAtom atom;

public:

#ifdef DEBUG
    static int counter;
#endif // DEBUG

    // Default constructor.
    Edge();

    // Default destructor.
    ~Edge();

    // Print function.
    friend ostream&
    operator<<(ostream& os,
               const Edge& e);
};

/// @}

}

#endif // MESH_EDGE_H
