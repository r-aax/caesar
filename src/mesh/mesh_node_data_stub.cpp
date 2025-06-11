/// \file
/// \brief Mesh node data stub implementaion.
///
/// Mesh node data stub implementation.

#include "mesh_node_data_stub.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

// Mapper initialization.
utils::Mapper<NodeDataElementStub> NodeDataStub::mapper
{
    "mesh node data element stub",
    vector<string>
    {
        "Stub"
    }
};

/// @}

}

}
