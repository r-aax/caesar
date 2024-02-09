/// \file
/// \brief Unstructured surface mesh declaration.
///
/// Declaration of unstructured surface mesh.

#ifndef MESH_UNSTRUCTURED_SURFACE_MESH_H
#define MESH_UNSTRUCTURED_SURFACE_MESH_H

#include "utils/utils.h"
#include "mesh_zone.h"

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

    // Zones list.
    vector<shared_ptr<Zone>> zones;

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
};

/// @}

}

#endif // MESH_UNSTRUCTURED_SURFACE_MESH_H
