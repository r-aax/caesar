/// \file
/// \brief Tests for mesh.
///
/// Tests for mesh.

#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include "caesar.h"

using namespace std;
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

        // Load mesh.
        Filer::load_mesh<NodeDataStub, NodeDataStub, CellDataStub>(mesh, "cases/meshes/sphere.dat");

        //
        // Set and get nodes data.
        //

        for (int i = 0; i < n; ++i)
        {
            in_data[i] = static_cast<double>(i + 1);
            out_data[i] = 0.0;
        }

        mesh.set_nodes_elements<NodeDataStub>(static_cast<int>(NodeDataElementStub::Stub),
                                              in_data, n);
        mesh.get_nodes_elements<NodeDataStub>(static_cast<int>(NodeDataElementStub::Stub),
                                              out_data, n);

        for (int i = 0; i < n; ++i)
        {
            CHECK(mth::is_eq(in_data[i], out_data[i]));
        }

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

        // Free data.
        mesh.clear();
    }

    SECTION("double load")
    {
        Mesh mesh;

        // Load mesh.
        Filer::load_mesh<NodeDataStub, NodeDataStub, CellDataStub>(mesh, "cases/meshes/sphere.dat");

        size_t nc1 { mesh.all.nodes_count() };
        size_t ec1 { mesh.all.edges_count() };
        size_t cc1 { mesh.all.cells_count() };
        size_t zc1 { mesh.zones_count() };

        // Load mesh.
        Filer::load_mesh<NodeDataStub, NodeDataStub, CellDataStub>(mesh, "cases/meshes/sphere.dat");

        size_t nc2 { mesh.all.nodes_count() };
        size_t ec2 { mesh.all.edges_count() };
        size_t cc2 { mesh.all.cells_count() };
        size_t zc2 { mesh.zones_count() };

        // Free data.
        mesh.clear();

        CHECK(nc1 == nc2);
        CHECK(ec1 == ec2);
        CHECK(cc1 == cc2);
        CHECK(zc1 == zc2);
    }
}
