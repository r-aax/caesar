/// \file
/// \brief Initialization of meshes edges colorizer.
///
/// Mesh edges colorizer initialization.

#ifndef CAESAR_MESH_EDGES_COLORIZER_H
#define CAESAR_MESH_EDGES_COLORIZER_H

#include "mesh_mesh.h"

namespace caesar
{

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

}

#endif // !CAESAR_MESH_EDGES_COLORIZER_H
