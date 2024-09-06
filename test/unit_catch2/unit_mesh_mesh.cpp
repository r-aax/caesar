/// \file
/// \brief Tests for mesh.
///
/// Tests for mesh.

#include <catch2/catch_test_macros.hpp>
#include "caesar.h"

using namespace caesar;

TEST_CASE("Mesh : main methods of mesh", "[mesh]")
{
    SECTION("init data")
    {
        mesh::Mesh mesh;

        mesh::Filer::load_mesh(mesh, "cases/meshes/sphere.dat");
        mesh.free_data_if_not_null();
    }
}
