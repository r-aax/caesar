/// \file
/// \brief Mesh cell declaration.
///
/// Mesh cell declaration.

#ifndef MESH_CELL_H
#define MESH_CELL_H

#include "mesh_edge.h"
#include "solver/solver.h"

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Mesh cell.
class Cell
{
    friend class Zone;

private:

    /// \brief Identifier.
    int id { -1 };

    /// \brief Links to nodes.
    vector<shared_ptr<Node>> nodes;

    /// \brief Links to edges.
    vector<shared_ptr<Edge>> edges;

    /// \brief Cell atom.
    solver::CellAtom atom;

public:

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
