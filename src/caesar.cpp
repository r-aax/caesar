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
    parl::mpi_init(&argc, &argv);

#if 0
    graph::Graph* g = graph::GraphFactory::create_cube_graph();

    g->edges_coloring_for_cubic_graph_with_bicolor_cycles_algorithm();
    g->print_info();

    delete g;
#endif

    mesh::Mesh mesh;

    mesh::Filer::load_mesh(mesh, "cases/meshes/sphere.dat");

    // Decompose mesh.
    mesh::Decomposer::decompose(mesh, mesh::DecompositionType::Pressure, 3);

    // Store with chosen data.
    mesh.set_variables_names(vector<string> { "X", "Y", "Z" },
                             vector<string> { "CellMark", "CellId", "Domain",
                                              "DistFromBorder", "DistFromCenter" });
    mesh::Filer::store_mesh(mesh, "out/sphere.dat");

    mesh.clear();

    parl::mpi_finalize();
}
