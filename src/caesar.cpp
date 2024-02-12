/// \file
/// \brief Main file.
///
/// This file contains entry point to CAEsar module.

#include "caesar.h"

int
main()
{
    mesh::UnstructuredSurfaceMesh m;

    m.load("cases/meshes/naca_mz.dat");
    m.store("res.dat");
    m.print_info();

    return 0;
}
