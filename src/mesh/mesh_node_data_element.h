/// \file
/// \brief Node data element enumeration.
///
/// Node data element enumeration.

#ifndef MESH_NODE_DATA_ELEMENT_H
#define MESH_NODE_DATA_ELEMENT_H

#include "utils/utils.h"

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Node data element.
enum class NodeDataElement
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

/// \brief Node data element mapper.
extern utils::Mapper<NodeDataElement> NodeDataElementMapper;

/// @}

}

#endif // !MESH_NODE_DATA_ELEMENT_H
