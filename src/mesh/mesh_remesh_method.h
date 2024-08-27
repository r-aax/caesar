/// \file
/// \brief Remesh method.
///
/// Remesh method declaration.

#ifndef CAESAR_MESH_REMESH_METHOD_H
#define CAESAR_MESH_REMESH_METHOD_H

#include "utils/utils_mapper.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Remesh method.
enum class RemeshMethod
{
    /// \brief First element.
    First = 0,

    /// \brief Prisms method.
    Prisms = First,

    /// \brief Tong method.
    Tong,

    /// \brief Last element.
    Last = Tong
};

/// \brief Remesh method mapper.
extern utils::Mapper<RemeshMethod> RemeshMethodMapper;

/// @}

}

}

#endif // !CAESAR_MESH_REMESH_METHOD_H
