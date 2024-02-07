/// \file
/// \brief Main file.
///
/// This file contains entry point to CAEsar module.

#include "caesar.h"

int
main()
{
    mesh::UnstructuredSurfaceMesh m;

    m.Load("cases/meshes/sphere.dat");

    return 0;
}
