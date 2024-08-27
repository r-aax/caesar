/// \file
/// \brief Graph factory.
///
/// Factory of graphs. Can create the following graphs:
/// - empty graph,
/// - trivial graph,
/// - full graph.

#ifndef CAESAR_GRAPH_GRAPH_FACTORY_H
#define CAESAR_GRAPH_GRAPH_FACTORY_H

#include "graph.h"

namespace caesar
{

namespace graph
{

/// \addtogroup graph
/// @{

/// \brief Graph factory declaration.
class GraphFactory
{

private:

public:

    // Create empty graph.
    static Graph*
    create_empty_graph();

    // Create graph without edges.
    static Graph*
    create_edgeless_graph(size_t n);

    /// \brief Create trivial graph.
    ///
    /// Create trivial graph.
    ///
    /// \return
    /// Trivial graph.
    static inline Graph*
    create_trivial_graph()
    {
        return create_edgeless_graph(1);
    }

    // Create complete graph.
    static Graph*
    create_complete_graph(size_t n);

    /// \brief Create tetrahedron graph.
    ///
    /// Create tetrahedron graph.
    ///
    /// \return
    /// Tetrahedron graph.
    static Graph*
    create_tetrahedron_graph()
    {
        return create_complete_graph(4);
    }

    // Create cyclic graph.
    static Graph*
    create_cyclic_graph(size_t n);

    // Create prizm graph.
    static Graph*
    create_prism_graph(size_t half_size);

    /// \brief Create cube graph.
    ///
    /// Create cube graph.
    ///
    /// \return
    /// Cube graph.
    static Graph*
    create_cube_graph()
    {
        return create_prism_graph(4);
    }
};

/// @}

}

}

#endif // !CAESAR_GRAPH_GRAPH_FACTORY_H
