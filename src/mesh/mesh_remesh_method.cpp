/// \file
/// \brief Remesh method.
///
/// Remesh method implementation.

#include "mesh_remesh_method.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Remesh method mapper.
utils::Mapper<RemeshMethod> RemeshMethodMapper
{
    "remesh method",
    vector<string> { "PRISMS", "TONG" }
};

/// @}

}

}
