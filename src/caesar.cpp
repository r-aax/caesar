/// \file
/// \brief Main module.
///
/// Main module.

#include "caesar.h"

using namespace caesar;

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

#if 0
    graph::Graph* g = graph::GraphFactory::create_cube_graph();

    g->edges_coloring_for_cubic_graph_with_bicolor_cycles_algorithm();
    g->print_info();

    delete g;
#endif

    mesh::Mesh mesh;
    mesh::Filer::load_mesh(mesh, "cases/meshes/sphere.dat");
    mesh::Filer::store_mesh(mesh, "res.dat");
    mesh.free_data_if_null();
}
