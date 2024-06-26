/// \file
/// \brief Main module.
///
/// Main module.

#include "graph/graph.h"

/// \brief Main function.
///
/// Main function - entry point into application.
///
/// \param[in] argc Number of arguments.
/// \param[in] argv Arguments.
///
/// \return
/// Retunr code.
int
main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    graph::Graph* g = graph::GraphFactory::create_cube_graph();

    g->edges_coloring_for_cubic_graph_with_bicolor_cycles_algorithm();
    g->print_info();

    delete g;
}
