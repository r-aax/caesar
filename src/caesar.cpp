/// \file
/// \brief Main file.
///
/// This file contains entry point to CAEsar module.

#include "caesar.h"

int
main()
{
    mesh::UnstructuredSurfaceMesh m;

    m.load("cases/meshes/sphere.dat");
    m.store("res.dat");

    return 0;
}