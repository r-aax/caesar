/// \file
/// \brief Mesh zone declaration.
///
/// Mesh zone declaration.

#ifndef MESH_ZONE_H
#define MESH_ZONE_H

#include "utils/utils.h"

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Mesh zone.
class Zone
{
    friend class UnstructuredSurfaceMesh;

private:

    // Name of zone.
    string name;

    // Count of nodes.
    int nodes_count;

    // Count of elements.
    int elements_count;

    // Varlocation cellcentered variables.
    pair<int, int> varlocation_cellcentered;

    // Loaded data.
    vector<vector<double>> data;

    // Links.
    vector<vector<int>> links;

public:

    // Default constructor.
    Zone();

    // Default destructor.
    ~Zone();

private:

    // Store data.
    void
    store_data(ofstream& f);

    // Store links.
    void
    store_links(ofstream& f);
};

/// @}

}

#endif // MESH_ZONE_H
