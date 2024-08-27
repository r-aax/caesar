/// \file
/// \brief Implementation of mesh decomposition type.

#include "mesh_decomposition_type.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Mesh decomposition type mapper.
utils::Mapper<DecompositionType> MeshDecompositionTypeMapper
{
    "mesh decomposition type",
    vector<string> { "NO", "RANDOM", "LINEAR" }
};

/// @}

}

}
