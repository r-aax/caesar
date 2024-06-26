/// \file
/// \brief Declaration of graph edge.
///
/// Declaration of graph edge.

#ifndef GRAPH_EDGE_H
#define GRAPH_EDGE_H

#include "graph_vertex.h"

namespace graph
{

/// \addtogroup graph
/// @{

/// \brief Graph edge.
class Edge
{

private:

    /// \brief Number of ends.
    const size_t const_vertices_count { 2 };

    /// \brief Identifier.
    int id { -1 };

    /// \brief Color.
    int color { -1 };

    /// \brief Incident vertices vector.
    vector<Vertex*> vertices;

public:

#ifdef DEBUG
    static int counter;
#endif // DEBUG

    // Constructor with id.
    Edge(int id_);

    // Default destructor.
    ~Edge();

    // Print function.
    friend ostream&
    operator<<(ostream& os,
               const Edge& e);

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

    /// \brief Get color.
    ///
    /// Get color.
    ///
    /// \return
    /// Color.
    inline int
    get_color() const
    {
        return color;
    }

    /// \brief Set color.
    ///
    /// Set color.
    ///
    /// \param[in] color_ Color.
    inline void
    set_color(int color_)
    {
        color = color_;
    }

    /// \brief Get vertices.
    ///
    /// Get vertices.
    ///
    /// \return
    /// Vertices.
    inline const vector<Vertex*>&
    get_vertices() const
    {
        return vertices;
    }

    /// \brief Get vertices count.
    ///
    /// Get vertices count.
    ///
    /// \return
    /// Vertices count.
    inline size_t
    vertices_count() const
    {
        return vertices.size();
    }

    /// \brief Check if edge is loop.
    ///
    /// Check if edge is loop.
    ///
    /// \return
    /// true - if edge is loop,
    /// false - otherwise.
    inline bool
    is_loop() const
    {
        return get_a() == get_b();
    }

    //
    // Arrange.
    //

    // Arrange vertices in identifiers increasing order.
    void
    arrange_vertices_increasing_ids();

    //
    // Relations with other elements.
    //

    // Check if edge is incident to vertex.
    bool
    is_incident(const Vertex* v) const;

    // Get end of the edge.
    Vertex*
    get_end(size_t i) const;

    /// \brief Get first end.
    ///
    /// Get first end.
    ///
    /// \return
    /// First end.
    inline Vertex*
    get_a() const
    {
        return vertices[0];
    }

    /// \brief Get second end.
    ///
    /// Get second end.
    ///
    /// \return
    /// Second end.
    inline Vertex*
    get_b() const
    {
        return vertices[1];
    }

    /// \brief Add vertex.
    ///
    /// Add vertex to vertices vector.
    ///
    /// \param[in] v Vertex.
    inline void
    add_vertex(Vertex* v)
    {
        vertices.push_back(v);
    }

    //
    // Reduce cubic graph.
    //

    // Check if edge is unique reduceable edge in cubic graph.
    bool
    is_cubic_graph_unique_reduceable_edge();

    // Check if edge is parallel reduceable edge in cubic graph.
    bool
    is_cubic_graph_parallel_reduceable_edge();

    //
    // Edge painting.
    //

    // Greedy paint.
    void
    greedy_paint();
};

/// @}

}

#endif // !GRAPH_EDGE_H
