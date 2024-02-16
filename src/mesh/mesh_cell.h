/// \file
/// \brief Mesh cell declaration.
///
/// Mesh cell declaration.

#ifndef MESH_CELL_H
#define MESH_CELL_H

#include "solver/solver_cell_core.h"

namespace mesh
{

/// \addtogroup mesh
/// @{

class Node;
class Edge;

/// \brief Mesh cell.
class Cell : public solver::CellCore
{
    friend class Zone;

private:

    /// \brief Identifier.
    int id { -1 };

    /// \brief Links to nodes.
    vector<shared_ptr<Node>> nodes;

    /// \brief Links to edges.
    vector<shared_ptr<Edge>> edges;

public:

#ifdef DEBUG
    static int counter;
#endif // DEBUG

    // Default constructor.
    Cell();

    // Default destructor.
    ~Cell();

    // Print function.
    friend ostream&
    operator<<(ostream& os,
               const Cell& c);
};

/// @}

}

#endif // MESH_CELL_H
