/// \file
/// \brief Mesh node data stub declaration.
///
/// Mesh node data stub declaration.

#ifndef MESH_NODE_DATA_STUB_H
#define MESH_NODE_DATA_STUB_H

#include "mesh_node.h"
#include "utils/utils.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Node data element stub.
///
/// Data elements for stub.
enum class NodeDataElementStub
{
    /// \brief First element.
    First = static_cast<int>(NodeElement::Last) + 1,

    /// \brief Stub.
    Stub = First,

    /// \brief Last element.
    Last = Stub
};

/// \brief Node data.
class NodeDataStub
{

public:

    /// \brief Mapper.
    ///
    /// Mapper.
    static utils::Mapper<NodeDataElementStub> mapper;

private:

    /// \brief Stub data.
    ///
    /// Stub data.
    double stub { 0.0 };

public:

    //
    // Data access.
    //

    /// \brief Get data from node.
    ///
    /// Get data from node.
    ///
    /// \param[in] index Data index.
    ///
    /// \return
    /// Data.
    inline double
    get_element(int index) const
    {
        NodeDataElementStub nde { static_cast<NodeDataElementStub>(index) };

        // Ignode wrong indices.
        return (nde == NodeDataElementStub::Stub) ? stub : 0.0;
    }

    /// \brief Set data to node.
    ///
    /// Set data to node.
    ///
    /// \param[in] index Data index.
    /// \param[in] v     Data value.
    inline void
    set_element(int index,
                double v)
    {
        NodeDataElementStub nde { static_cast<NodeDataElementStub>(index) };

        // Ignore wrong indices.
        if (nde == NodeDataElementStub::Stub)
        {
            stub = v;
        }
    }
};

/// @}

}

}

#endif // !MESH_NODE_DATA_STUB_H
