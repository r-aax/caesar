/// \file
/// \brief Main module.
///
/// Main module.

#include "caesar.h"

/// \brief Main function.
///
/// Main function - entry point into application.
///
/// \param[in] argc Number of arguments.
/// \param[in] argv Arguments.
///
/// \return
/// Return code.
int
main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    caesar::graph::Graph* g = caesar::graph::GraphFactory::create_cube_graph();

    g->edges_coloring_for_cubic_graph_with_bicolor_cycles_algorithm();
    g->print_info();

    delete g;
}
