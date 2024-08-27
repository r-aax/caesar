/// \file
/// \brief Node data element.
///
/// Node data element enumeration.

#include "mesh_node_data_element.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Node data element mapper.
utils::Mapper<NodeDataElement> NodeDataElementMapper
{
    "node data element",
    vector<string>
    {
        "X", "Y", "Z",
        "NodeMark", "NodeId"
    }
};

/// @}

}

}
