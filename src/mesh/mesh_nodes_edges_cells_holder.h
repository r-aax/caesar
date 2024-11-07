/// \file
/// \brief Nodes, edges and cells holder.
///
/// Class that holds nodes, edges and cells.

#ifndef MESH_NODES_EDGES_CELLS_HOLDER_H
#define MESH_NODES_EDGES_CELLS_HOLDER_H

#include "mesh_nodes_holder.h"
#include "mesh_edges_holder.h"
#include "mesh_cells_holder.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Nodes, edges, cells holder.
///
/// Class that holds all objects - nodes, edges, cells.
class NodesEdgesCellsHolder
    : public NodesHolder,
      public EdgesHolder,
      public CellsHolder
{

public:

    /// \brief Clear all elements.
    ///
    /// Clear all elements.
    inline void
    clear()
    {
        clear_nodes();
        clear_edges();
        clear_cells();
    }
};

/// @}

}

}

#endif // !MESH_NODS_EDGES_CELLS_HOLDER_H
