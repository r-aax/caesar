/// \file
/// \brief Mesh decomposer class.
///
/// Mesh decomposer.

#ifndef MESH_DECOMPOSER_H
#define MESH_DECOMPOSER_H

#include "mesh_mesh.h"
#include "mesh_decomposition_type.h"

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Decomposer class.
class Decomposer
{

private:

    // Set domain number to cells diapason.
    static void
    set_cells_diapason_with_domain(Mesh& mesh,
                                   size_t lo,
                                   size_t hi,
                                   size_t domain);

    // Decompose with type NO.
    static void
    decompose_no(Mesh& mesh);

    // Random decomposition.
    static void
    decompose_random(Mesh& mesh,
                     size_t dn);

    // Linear decomposition.
    static void
    decompose_linear(Mesh& mesh,
                     size_t dn);

    // Post decompose action.
    static void
    post_decompose(Mesh& mesh);

public:

    // Decompose mesh.
    static void
    decompose(Mesh& mesh,
              DecompositionType type,
              size_t dn);
};

/// @}

}

#endif // !MESH_DECOMPOSER_H
