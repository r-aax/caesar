/// \file
/// \brief Initialization of meshes edges colorizer.
///
/// Mesh edges colorizer initialization.

#ifndef MESH_EDGES_COLORIZER_H
#define MESH_EDGES_COLORIZER_H

#include "mesh_mesh.h"

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Mesh edges colorizer.
class EdgesColorizer
{

public:

    // Colorize edges.
    static void
    colorize_edges(Mesh& mesh);
};

/// @}

}

#endif // !MESH_EDGES_COLORIZER_H
