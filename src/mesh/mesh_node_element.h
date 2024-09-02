/// \file
/// \brief Node element enumeration.
///
/// Node element enumeration.

#ifndef CAESAR_MESH_NODE_ELEMENT_H
#define CAESAR_MESH_NODE_ELEMENT_H

#include "utils/utils.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Node element.
enum class NodeElement
{
    /// \brief First element.
    First = 0,

    /// \brief X coordinate.
    X = First,

    /// \brief Y coordinate.
    Y,

    /// \brief Z coordinate.
    Z,

    /// \brief Node mark (for technical use).
    NodeMark,

    /// \brief Node identifier.
    NodeId,

    /// \brief Last element.
    Last = NodeId
};

/// \brief Node element mapper.
extern utils::Mapper<NodeElement> NodeElementMapper;

/// @}

}

}

#endif // !CAESAR_MESH_NODE_ELEMENT_H
