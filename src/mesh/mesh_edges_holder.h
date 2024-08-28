/// \file
/// \brief Class that holds edges.
///
/// Class that holds edges.

#ifndef CAESAR_MESH_EDGES_HOLDER_H
#define CAESAR_MESH_EDGES_HOLDER_H

#include <vector>

using namespace std;

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

class Edge;

/// \brief Class that holds edges
///
/// Class that holds edges.
class EdgesHolder
{

private:

    /// \brief Vector of edges pointers.
    vector<Edge*> edges_;

public:

    /// \brief Get edges (const version).
    ///
    /// Get edges (const verstion).
    ///
    /// \return
    /// Edges (const version).
    inline const vector<Edge*>&
    edges() const
    {
        return edges_;
    }

    /// \brief Get edges.
    ///
    /// Get edges.
    ///
    /// \return
    /// Edges.
    inline vector<Edge*>&
    edges()
    {
        return edges_;
    }

    /// \brief Get count of edges.
    ///
    /// Get count of edges.
    ///
    /// \return
    /// Count of edges.
    inline size_t
    edges_count() const
    {
        return edges_.size();
    }

    /// \brief Add edge.
    ///
    /// Add edge.
    ///
    /// \param[in] e Edge pointer.
    inline void
    add_edge(Edge* e)
    {
        edges_.push_back(e);
    }

    /// \brief Get edge (const version).
    ///
    /// Get edge (const version).
    ///
    /// \param[in] i Index of edge.
    ///
    /// \return
    /// Pointer to edge (const version).
    inline const Edge*
    edge(size_t i) const
    {
        return edges_[i];
    }

    /// \brief Get edge.
    ///
    /// Get edge.
    ///
    /// \param[in] i Index of edge.
    ///
    /// \return
    /// Pointer to edge.
    inline Edge*
    edge(size_t i)
    {
        return edges_[i];
    }
};

/// @}

}

}

#endif // !CAESAR_MESH_EDGES_HOLDER_H
