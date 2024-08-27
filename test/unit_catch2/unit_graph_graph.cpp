/// \file
/// \brief Graph tests.
///
/// Graph tests.

#include <catch2/catch_test_macros.hpp>
#include "graph/graph.h"

TEST_CASE("Graph : undirected graphs", "[graph]")
{
    SECTION("adding unique and parallel edges")
    {
        graph::Graph* g = graph::GraphFactory::create_empty_graph();

        graph::Vertex* a = g->new_vertex();
        graph::Vertex* b = g->new_vertex();

        g->add_edge(a, b);
        CHECK(!g->has_parallel_edges());
        graph::Edge* e = g->add_unique_edge(a, b);
        CHECK(e == nullptr);
        e = g->add_edge(a, b);
        CHECK(a->has_parallel_edges());
        CHECK(g->has_parallel_edges());

        delete g;
    }

    SECTION("creation and global properties")
    {
        graph::Graph* empty_graph = graph::GraphFactory::create_empty_graph();
        graph::Graph* edgeless_graph = graph::GraphFactory::create_edgeless_graph(5);
        graph::Graph* trivial_graph = graph::GraphFactory::create_trivial_graph();
        graph::Graph* complete_graph = graph::GraphFactory::create_complete_graph(5);

        CHECK(empty_graph->is_empty());
        CHECK(empty_graph->is_regular(0));
        CHECK(edgeless_graph->is_edgeless());
        CHECK(edgeless_graph->is_regular(0));
        CHECK(trivial_graph->is_trivial());
        CHECK(trivial_graph->is_regular(0));
        CHECK(complete_graph->is_complete());
        CHECK(complete_graph->is_regular(4));

        delete empty_graph;
        delete edgeless_graph;
        delete trivial_graph;
        delete complete_graph;
    }

    SECTION("reduce by unique edge")
    {
        graph::Graph* g = graph::GraphFactory::create_complete_graph(4);

        g->reduce_cubic_graph_by_unique_edge(g->get_edge(0));

        // Out graph now is minimal cubic.
        CHECK(g->is_minimal_cubic());
        CHECK(g->has_parallel_edges());

        delete g;
    }

    SECTION("full reduce by unique edge and restore")
    {
        size_t half_size { 5 };
        graph::Graph* g1 = graph::GraphFactory::create_prism_graph(half_size);
        graph::Graph* g2 = graph::GraphFactory::create_prism_graph(half_size);
        graph::CubicGraphReduceHistory h;
        graph::Edge* e { nullptr };

        CHECK(graph::Graph::is_strong_isomorphic(*g1, *g2));

        e = g1->get_cubic_graph_unique_reduceable_edge();

        while (e != nullptr)
        {
            g1->reduce_cubic_graph_by_unique_edge(e, &h);
            e = g1->get_cubic_graph_unique_reduceable_edge();
        }

        CHECK(!g1->is_minimal_cubic());
        CHECK(!graph::Graph::is_strong_isomorphic(*g1, *g2));

        // Restore.
        g1->restore_cubic_graph(h);

        CHECK(graph::Graph::is_strong_isomorphic(*g1, *g2));

        delete g1;
        delete g2;
    }

    SECTION("full reduce and restore from prizm graph to smaller cubic")
    {
        size_t half_size { 7 };
        graph::Graph* g1 = graph::GraphFactory::create_prism_graph(half_size);
        graph::Graph* g2 = graph::GraphFactory::create_prism_graph(half_size);
        graph::CubicGraphReduceHistory h;

        CHECK(graph::Graph::is_strong_isomorphic(*g1, *g2));

        g1->full_reduce_cubic_graph(&h);

        CHECK(g1->is_minimal_cubic());

        // Restore.
        g1->restore_cubic_graph(h);

        CHECK(graph::Graph::is_strong_isomorphic(*g1, *g2));

        delete g1;
        delete g2;
    }

    SECTION("greedy graph edges coloring")
    {
        graph::Graph* g = graph::GraphFactory::create_prism_graph(6);

        CHECK(g->edges_coloring_greedy() == 3);

        delete g;
    }
}
