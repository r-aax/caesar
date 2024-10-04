/// \file
/// \brief Tests for mesh.
///
/// Tests for mesh.

#include <catch2/catch_test_macros.hpp>
#include "caesar.h"

using namespace caesar;
using namespace caesar::mesh;

TEST_CASE("Mesh : main methods of mesh", "[mesh]")
{
    SECTION("init data")
    {
        const int n { 5 };
        double in_data[n];
        double out_data[n];
        Mesh mesh;

        Filer::load_mesh(mesh, "cases/meshes/sphere.dat");

        //
        // Set and get cells data.
        //

        for (int i = 0; i < n; ++i)
        {
            in_data[i] = static_cast<double>(i + 1);
            out_data[i] = 0.0;
        }

        mesh.set_cells_elements<CellDataStub>(static_cast<int>(CellDataElementStub::Stub),
                                              in_data, n);
        mesh.get_cells_elements<CellDataStub>(static_cast<int>(CellDataElementStub::Stub),
                                              out_data, n);

        for (int i = 0; i < n; ++i)
        {
            CHECK(mth::is_eq(in_data[i], out_data[i]));
        }

        mesh.free_data_if_not_null();
    }
}
