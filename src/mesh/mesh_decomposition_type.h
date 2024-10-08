/// \file
/// \brief Mesh decomposition type declaration.
///
/// Declaration of mesh decomposition type.

#ifndef CAESAR_MESH_DECOMPOSITION_TYPE_H
#define CAESAR_MESH_DECOMPOSITION_TYPE_H

#include "utils/utils.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Decomposition type.
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

    /// \brief Decomposition based on pressure principle.
    Pressure,

    /// \brief Last element.
    Last = Pressure
};

/// \brief Mesh decomposition type mapper.
extern utils::Mapper<DecompositionType> MeshDecompositionTypeMapper;

/// @}

}

}

#endif // !CAESAR_MESH_DECOMPOSITION_TYPE_H
