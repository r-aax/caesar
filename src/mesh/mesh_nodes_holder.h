/// \file
/// \brief Class that holds nodes.
///
/// Class that holds nodes.

#ifndef CAESAR_MESH_NODES_HOLDER_H
#define CAESAR_MESH_NODES_HOLDER_H

#include <vector>

using namespace std;

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

class Node;

/// \brief Class that holds nodes
///
/// Class that holds nodes.
class NodesHolder
{

private:

    /// \brief Vector of nodes pointers.
    vector<Node*> nodes_;

public:

    /// \brief Get nodes (const version).
    ///
    /// Get nodes (const verstion).
    ///
    /// \return
    /// Nodes (const version).
    inline const vector<Node*>&
    nodes() const
    {
        return nodes_;
    }

    /// \brief Get nodes.
    ///
    /// Get nodes.
    ///
    /// \return
    /// Nodes.
    inline vector<Node*>&
    nodes()
    {
        return nodes_;
    }

    /// \brief Get count of nodes.
    ///
    /// Get count of nodes.
    ///
    /// \return
    /// Count of nodes.
    inline size_t
    nodes_count() const
    {
        return nodes_.size();
    }

    /// \brief Add node.
    ///
    /// Add node.
    ///
    /// \param[in] n Node pointer.
    inline void
    add_node(Node* n)
    {
        nodes_.push_back(n);
    }

    /// \brief Clear.
    ///
    /// Clear all elements.
    inline void
    clear_nodes()
    {
        nodes_.clear();
    }

    /// \brief Get node (const version).
    ///
    /// Get node (const version).
    ///
    /// \param[in] i Index of node.
    ///
    /// \return
    /// Pointer to node (const version).
    inline const Node*
    node(size_t i) const
    {
        return nodes_[i];
    }

    /// \brief Get node.
    ///
    /// Get node.
    ///
    /// \param[in] i Index of node.
    ///
    /// \return
    /// Pointer to node.
    inline Node*
    node(size_t i)
    {
        return nodes_[i];
    }
};

/// @}

}

}

#endif // !CAESAR_MESH_NODES_HOLDER_H
