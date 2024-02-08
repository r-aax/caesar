/// \file
/// \brief Unstructured surface mesh declaration.
///
/// Declaration of unstructured surface mesh.

#ifndef MESH_UNSTRUCTURED_SURFACE_MESH_H
#define MESH_UNSTRUCTURED_SURFACE_MESH_H

#include "utils/utils.h"

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Unstructured surface mesh.
class UnstructuredSurfaceMesh
{

private:

    // Title.
    string title;

    // Variables names.
    vector<string> variables_names;

    // Name of zone.
    string zone_name;

    // Count of nodes.
    int nodes_count;

    // Count of elements.
    int elements_count;

    // Lower bound of cellcentered varlocation.
    int varlocation_cellcentered_lo;

    // Varlocation cellcentered variables.
    pair<int, int> varlocation_cellcentered;

    // Loaded data.
    vector<vector<double>> data;

    // Links.
    vector<vector<int>> links;

public:

    // Constructor.
    UnstructuredSurfaceMesh();

    // Destructor.
    ~UnstructuredSurfaceMesh();

    // Load.
    bool
    load(const string& fn);

    // Store.
    bool
    store(const string& fn);

private:

    // Store variables names.
    void
    store_variables_names(ofstream& f);

    // Store data.
    void
    store_data(ofstream& f);

    // Store links.
    void
    store_links(ofstream& f);
};

/// @}

}

#endif // MESH_UNSTRUCTURED_SURFACE_MESH_H
