/// \file
/// \brief Mesh node data element stub enumeration.
///
/// Mesh node data element stub enumeration.

#ifndef MESH_NODE_DATA_ELEMENT_STUB_H
#define MESH_NODE_DATA_ELEMENT_STUB_H

#include "mesh_node_element.h"
#include "utils/utils.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Node data element stub.
enum class NodeDataElementStub
{
    /// \brief First element.
    First = static_cast<int>(NodeElement::Last) + 1,

    /// \brief Stub.
    Stub = First,

    /// \brief Last element.
    Last = Stub
};

/// \brief Node data element mapper stub.
extern utils::Mapper<NodeDataElementStub> NodeDataElementStubMapper;

/// @}

}

}

#endif // !MESH_NODE_DATA_ELEMENT_STUB_H
