/// \file
/// \brief Mesh decomposer class.
///
/// Mesh decomposer.

#ifndef CAESAR_MESH_DECOMPOSER_H
#define CAESAR_MESH_DECOMPOSER_H

#include "mesh_mesh.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Decomposition type.
///
/// Decomposition type.
enum class DecompositionType
{
    /// \brief First element.
    First = 0,

    /// \brief Single domain - no decomposition.
    No = First,

    /// \brief Random decomposition between domains.
    Random,

    /// \brief Linear decomposition.
    Linear,

    /// \brief Farhat decomposition.
    Farhat,

    /// \brief Last element.
    Last = Farhat
};

/// \brief Mesh decomposition type mapper.
///
/// Mesh decomposition type mapper.
extern utils::Mapper<DecompositionType> MeshDecompositionTypeMapper;

/// \brief Decomposer class.
///
/// Decomposer type.
class Decomposer
{

private:

    // Set domain number to cells diapason.
    static void
    set_cells_diapason_with_domain(Mesh& mesh,
                                   size_t lo,
                                   size_t hi,
                                   size_t domain);

    // Calculate cells dist from border.
    static void
    calc_cells_dist_from_border(Mesh& mesh);

    // Calculate cells dist from center.
    static void
    calc_cells_dist_from_center(Mesh& mesh);

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

    // Farhat decomposition.
    static void
    decompose_farhat(Mesh& mesh,
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

}

#endif // !CAESAR_MESH_DECOMPOSER_H
