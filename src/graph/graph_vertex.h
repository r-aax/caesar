/// \file
/// \brief Declaration of graph vertex.
///
/// Declaration of graph vertex.

#ifndef GRAPH_VERTEX_H
#define GRAPH_VERTEX_H

#include "utils/utils.h"

namespace graph
{

/// \addtogroup graph
/// @{

class Edge;

/// \brief Graph vertex.
class Vertex
{

private:

    /// \brief Identifier.
    int id { -1 };

    /// \brief Incident edges vector.
    vector<Edge*> edges;

public:

#ifdef DEBUG
    static int counter;
#endif // DEBUG

    // Constructor by identifier.
    Vertex(int id_);

    // Default destructor.
    ~Vertex();

    // Print function.
    friend ostream&
    operator<<(ostream& os,
               const Vertex& v);

    //
    // Basic properties.
    //

    /// \brief Get identifier.
    ///
    /// Get identifier.
    ///
    /// \return
    /// Identifier.
    inline int
    get_id() const
    {
        return id;
    }

    /// \brief Set identifier.
    ///
    /// Set identifier.
    ///
    /// \param[in] id_ Value.
    inline void
    set_id(int id_)
    {
        id = id_;
    }

    /// \brief Get identifier as string.
    ///
    /// Get identifier as string.
    ///
    /// \return
    /// Identifier string.
    inline string
    get_id_str() const
    {
        return to_string(get_id());
    }

    /// \brief Get edges.
    ///
    /// Get edges.
    ///
    /// \return
    /// Edges.
    inline const vector<Edge*>&
    get_edges() const
    {
        return edges;
    }

    /// \brief Count of edges.
    ///
    /// Get count of edges.
    ///
    /// \return
    /// Edges count.
    inline size_t
    edges_count() const
    {
        return edges.size();
    }

    /// \brief Degree of vertex.
    ///
    /// Degree (number of incident edges).
    ///
    /// \return
    /// Degree.
    inline size_t
    degree() const
    {
        return edges_count();
    }

    /// \brief Check if vertex is isolated.
    ///
    /// Check if vertex is isolated.
    ///
    /// \return
    /// true - if vertex is isolated,
    /// false - otherwise.
    inline bool
    is_isolated() const
    {
        return degree() == 0;
    }

    /// \brief Check if vertex is leaf.
    ///
    /// Check if vertex is leaf.
    ///
    /// \return
    /// true - if vertex is leaf,
    /// false - otherwise.
    inline bool
    is_leaf() const
    {
        return degree() == 1;
    }

    //
    // Arrange.
    //

    // Arrange edges in identifiers increasing order.
    void
    arrange_edges_increasing_ids();

    //
    // Relations with other elements.
    //

    // Check if vertex incident to edge.
    bool
    is_incident(const Edge* e) const;

    // Get edge.
    Edge*
    get_edge(size_t i) const;

    /// \brief Add edge.
    ///
    /// Add edge to edges.
    ///
    /// \param[in] e Edge.
    inline void
    add_edge(Edge* e)
    {
        edges.push_back(e);
    }

    // Get neighbour by edge.
    Vertex*
    neighbour(const Edge* e) const;

    // Find edge to another vertex.
    Edge*
    find_edge(const Vertex* v) const;

    /// \brief Check if vertex is adjacent to vertex.
    ///
    /// Check if vertex is adjacent to vertex.
    ///
    /// \param[in] v Vertex.
    ///
    /// \return
    /// true - if vertex is adjacent to vertex,
    /// false - otherwise.
    bool
    is_adjacent(const Vertex* v) const
    {
        return find_edge(v) != nullptr;
    }

    // Check if there is parallel edges from this vertex.
    bool
    has_parallel_edges() const;

    // Check if edges coloring is correct.
    bool
    is_edges_coloring_correct() const;

    // Remove edge.
    void
    remove_edge(Edge* e);
};

/// @}

}

#endif // !GRAPH_VERTEX_H
