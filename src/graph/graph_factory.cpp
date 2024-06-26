/// \file
/// \brief Graph factory implementation.
///
/// Graph factory implementation.

#include "graph_factory.h"

namespace graph
{

/// \addtogroup graph
/// @{

/// \brief Create empty graph.
///
/// Create empty graph.
///
/// \return
/// Empty graph.
Graph*
GraphFactory::create_empty_graph()
{
    Graph* g = new Graph();

    return g;
}

/// \brief Create graph without edges.
///
/// Create graph without edges.
///
/// \param[in] n Number of vertices.
///
/// \return
/// Graph.
Graph*
GraphFactory::create_edgeless_graph(size_t n)
{
    Graph* g = create_empty_graph();

    for (size_t i = 0; i < n; ++i)
    {
        g->new_vertex();
    }

    return g;
}

/// \brief Create complete graph.
///
/// Create complete graph.
///
/// \param[in] n Size of graph.
///
/// \return
/// Complete graph.
Graph*
GraphFactory::create_complete_graph(size_t n)
{
    Graph* g = create_edgeless_graph(n);

    // Create edges.
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = i + 1; j < n; ++j)
        {
            g->add_edge(i, j);
        }
    }

    return g;
}

/// \brief Create cyclic graph.
///
/// Create graph which is cycle of size n.
Graph*
GraphFactory::create_cyclic_graph(size_t n)
{
    Graph* g = create_edgeless_graph(n);

    g->add_cycle(0, n - 1);

    return g;
}

/// \brief Create prizm graph.
///
/// Create prism graph.
///
///      -----------------------
///     |       upper disc      |
///     *-----*-----*-----*-----*
///     |     |     |     |     |
///     |     |     |     |     |
///     *-----*-----*-----*-----*
///     |       lower disc      |
///      -----------------------
///
/// \param[in] half_size Size of disc.
///
/// \return
/// Prism graph.
Graph*
GraphFactory::create_prism_graph(size_t half_size)
{
    Graph* g = create_edgeless_graph(2 * half_size);

    // Add upper and lower discs.
    g->add_cycle(0, half_size - 1);
    g->add_cycle(half_size, 2 * half_size - 1);

    // Add vertical edges.
    for (size_t i = 0; i < half_size; ++i)
    {
        g->add_edge(i, i + half_size);
    }

    g->arrange_objects_increasing_ids();

    return g;
}

/// @}

}
