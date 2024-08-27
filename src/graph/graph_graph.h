/// \file
/// \brief Declaration of graph.
///
/// Declaration of graph.

#ifndef CAESAR_GRAPH_GRAPH_H
#define CAESAR_GRAPH_GRAPH_H

#include <iostream>

#include "utils/utils.h"
#include "graph_vertex.h"
#include "graph_edge.h"
#include "graph_cubic_graph_reduce_history.h"
#include "graph_bicolor_cycle.h"

using namespace std;

namespace caesar
{

namespace graph
{

/// \addtogroup graph
/// @{

/// \brief Graph.
///
/// Common graph declaration.
///
/// - Graph is not directed.
/// - Graph does not contain loops.
/// - Graph can contain parallel (multiple) edges.
class Graph
{

private:

    /// \brief Vertices vector.
    vector<Vertex*> vertices;

    /// \brief Maximum vertex id.
    int max_vertex_id { -1 };

    /// \brief Edges vector.
    vector<Edge*> edges;

    /// \brief Maximum edge id.
    int max_edge_id { -1 };

public:

#ifdef DEBUG
    static int counter;
#endif // DEBUG

    // Default constructor.
    Graph();

    // Default destructor.
    ~Graph();

    // Print information.
    void
    print_info(ostream& os = cout);

    //
    // Basic properties.
    //

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

    /// \brief Get graph order.
    ///
    /// Get graph order.
    ///
    /// \return
    /// Graph order.
    inline size_t
    order() const
    {
        return vertices_count();
    }

    /// \brief Get graph edges.
    ///
    /// Get graph edges.
    ///
    /// \return
    /// Graph edges.
    inline const vector<Edge*>&
    get_edges() const
    {
        return edges;
    }

    /// \brief Get edges count.
    ///
    /// Get edges count.
    ///
    /// \return
    /// Edges count.
    inline size_t
    edges_count() const
    {
        return edges.size();
    }

    /// \brief Get graph size.
    ///
    /// Get graph size.
    ///
    /// \return
    /// Graph size.
    inline size_t
    size() const
    {
        return edges_count();
    }

    //
    // Graph constructing.
    //

    // Get graph vertex.
    Vertex*
    get_vertex(size_t i) const;

    // Get graph edge.
    Edge*
    get_edge(size_t i) const;

    // Get random vertex.
    Vertex*
    get_random_vertex() const;

    // Get random edge.
    Edge*
    get_random_edge() const;

    // Find vertex by id.
    Vertex*
    find_vertex_by_id(int id_) const;

    // Find edge by id.
    Edge*
    find_edge_by_id(int id_) const;

    // Create new vertex with given identifier.
    Vertex*
    new_vertex(int id);

    /// \brief Create new vertex.
    ///
    /// Create and return new vertex.
    ///
    /// \return
    /// New vertex.
    inline Vertex*
    new_vertex()
    {
        return new_vertex(++max_vertex_id);
    }

    /// \brief Find edge between two vertices.
    ///
    /// Find edge between two vertices.
    ///
    /// \param[in] a First vertex.
    /// \param[in] b Second vertex.
    ///
    /// \return
    /// Found edge or nullptr.
    inline Edge*
    find_edge(const Vertex* a,
              const Vertex* b) const
    {
        return a->find_edge(b);
    }

    /// \brief Find edge by vertices indices.
    ///
    /// Find edge by vertices indices.
    ///
    /// \param[in] ai Index of the first vertex.
    /// \param[in] bi Index of the second vertex.
    ///
    /// \return
    /// Found edge or nullptr.
    inline Edge*
    find_edge(size_t ai,
              size_t bi) const
    {
        return find_edge(vertices[ai], vertices[bi]);
    }

    /// \brief Check if there is edge between two vertices.
    ///
    /// Check if there is edge between two vertices.
    ///
    /// \param[in] a First vertex.
    /// \param[in] b Second vertex.
    ///
    /// \return
    /// true - if there is an edge,
    /// false - otherwise.
    inline bool
    has_edge(const Vertex* a,
             const Vertex* b) const
    {
        return a->is_adjacent(b);
    }

    /// \brief Check if there is an edge between vertices.
    ///
    /// Check edge existence by vertices indices.
    ///
    /// \param[in] ai Index of the first vertex.
    /// \param[in] bi Index of the second vertex.
    ///
    /// \return
    /// true - if the edge exists,
    /// false - otherwise.
    inline bool
    has_edge(size_t ai,
             size_t bi) const
    {
        return has_edge(vertices[ai], vertices[bi]);
    }

    // Add edge with given identifier between two vertices.
    Edge*
    add_edge(Vertex* a,
             Vertex* b,
             int id);

    /// \brief Add edge between two vertices.
    ///
    /// Add new edge between two vertices.
    /// Double edges are not allowed.
    ///
    /// \param[in] a First vertex.
    /// \param[in] b Second vertex.
    ///
    /// \return
    /// New edge.
    inline Edge*
    add_edge(Vertex* a,
             Vertex* b)
    {
        return add_edge(a, b, ++max_edge_id);
    }

    /// \brief Add edge by vertices indices.
    ///
    /// Add edge by vertices indices.
    ///
    /// \param[in] ai Index of the first vertex.
    /// \param[in] bi Index of the second vertex.
    ///
    /// \return
    /// New edge.
    inline Edge*
    add_edge(size_t ai,
             size_t bi)
    {
        return add_edge(vertices[ai], vertices[bi]);
    }

    // Add unique edge between two vertices.
    Edge*
    add_unique_edge(Vertex* a,
                    Vertex* b);

    /// \brief Add unique edge by vertices indices.
    ///
    /// Add unique edge by vertices indices.
    ///
    /// \param[in] ai Index of the first vertex.
    /// \param[in] bi Index of the second vertex.
    ///
    /// \return
    /// New edge,
    /// or nullptr, if the edge already exists.
    inline Edge*
    add_unique_edge(size_t ai,
                    size_t bi)
    {
        return add_unique_edge(vertices[ai], vertices[bi]);
    }

    // Add cycle for range of verties.
    void
    add_cycle(size_t fromi,
              size_t toi);

    // Check if graph contains parallel edges.
    bool
    has_parallel_edges() const;

    //
    // Graph arranging.
    //

    // Reset identifiers.
    void
    reset_identifiers();

    // Arrange all objects in identifiers increasing order.
    void
    arrange_objects_increasing_ids();

    //
    // Global properties.
    //

    // Check if graph is empty.
    bool
    is_empty() const;

    /// \brief Check if graph is edgeless.
    ///
    /// Check if graph is edgeless.
    ///
    /// \return
    /// true - if graph is edgeless,
    /// false - otherwise.
    inline bool
    is_edgeless() const
    {
        return size() == 0;
    }

    // Check if graph is trivial.
    bool
    is_trivial() const;

    // Check if graph is complete.
    bool
    is_complete() const;

    // Check if graph is regular.
    bool
    is_regular(size_t d) const;

    /// \brief Check if graph is cubic.
    ///
    /// Graph is cubic if it is regular with degree 3.
    ///
    /// \return
    /// true - if graph is cubic,
    /// false - otherwise.
    bool
    is_cubic() const
    {
        return is_regular(3);
    }

    // Check graph is minimal cubic.
    bool
    is_minimal_cubic() const;

    // Check for strong isomorphic of two graphs.
    static bool
    is_strong_isomorphic(const Graph& g1,
                         const Graph& g2);

    //
    // Graph modifications.
    //

    // Remove edge from graph.
    void
    remove_edge(Edge* e);

    // Remove vertex from graph.
    void
    remove_vertex(Vertex* v);

    // Bubble cubic graph vertex.
    void
    bubble_cubic_graph_vertex(Vertex* v);

    // Bubble cubic graph vertex.
    void
    bubble_cubic_graph_vertex();

    //
    // Cubic graph reduce and restore.
    //

    // Glue two edges incident to vertex.
    Edge*
    glue_two_incident_edges(Vertex* v,
                            int& e1_id,
                            int& e2_id);

    // Glue two hangind edges.
    Edge*
    glue_two_hanging_edges(Vertex* v1,
                           Vertex* v2,
                           bool& is_new_edge_reversed);

    // Get cubic graph unique reduceable edge.
    Edge*
    get_cubic_graph_unique_reduceable_edge();

    // Get cubuc graph parallel_reduceable edge.
    Edge*
    get_cubic_graph_parallel_reduceable_edge();

    // Reduce cubic graph graph by unique edge.
    void
    reduce_cubic_graph_by_unique_edge(Edge* e,
                                      CubicGraphReduceHistory* h = nullptr);

    // Reduce cubic graph graph by parallel edge.
    void
    reduce_cubic_graph_by_parallel_edge(Edge* e,
                                        CubicGraphReduceHistory* h = nullptr);

    // Full reduce cubic graph.
    int
    full_reduce_cubic_graph(CubicGraphReduceHistory* h = nullptr);

    // Restore cubic graph step for unique edge.
    void
    restore_cubic_graph_step_unique_edge(const CubicGraphReduceHistory& h);

    // Restore cubic graph step for parallel edge.
    void
    restore_cubic_graph_step_parallel_edge(const CubicGraphReduceHistory& h);

    // Restore cubic graph one step.
    void
    restore_cubic_graph_step(CubicGraphReduceHistory& h);

    // Restore cubic graph (all steps).
    void
    restore_cubic_graph(CubicGraphReduceHistory& h);

    //
    // Graph coloring.
    //

    // Fill edges colors histogram.
    void
    fill_edges_colors_histogram(vector<int>& h) const;

    // Greedy algorithm of edges coloring.
    int
    edges_coloring_greedy();

    // Restore and repaint cubic graph step for unique edge.
    void
    restore_and_repaint_cubic_graph_step_unique_edge(const CubicGraphReduceHistory& h,
                                                     BicolorCycle& bc,
                                                     Edge* result_e1,
                                                     Edge* result_e2);

    // Restore and repaint cubic graph step for unique edge when colors are equal.
    void
    restore_and_repaint_cubic_graph_step_unique_edge_eq_colors(const CubicGraphReduceHistory& h,
                                                               Edge* result_e1,
                                                               Edge* result_e2);

    // Restore and repaint cubic graph step for unique edge colors are not equal.
    void
    restore_and_repaint_cubic_graph_step_unique_edge_ne_colors(const CubicGraphReduceHistory& h,
                                                               Edge* result_e1,
                                                               Edge* result_e2);

    // Restore and repaint cubic graph step for unique edge.
    void
    restore_and_repaint_cubic_graph_step_unique_edge(const CubicGraphReduceHistory& h);

    // Restore and repaint cubic graph step for parallel edge.
    void
    restore_and_repaint_cubic_graph_step_parallel_edge(const CubicGraphReduceHistory& h);

    // Edges coloring for cubic graph using bicolor cycles.
    void
    edges_coloring_for_cubic_graph_with_bicolor_cycles_algorithm();

    // Check if edges coloring is coorect.
    bool
    is_edges_coloring_correct() const;
};

/// @}

}

}

#endif // !CAESAR_GRAPH_GRAPH_H
