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

    // Get title from string.
    void
    get_title_from_string(const string& s);

    // Get variables names from string.
    void
    get_variables_names_from_string(const string& s);

    // Store variables names.
    void
    store_variables_names(ofstream& f);
};

/// @}

}

#endif // MESH_UNSTRUCTURED_SURFACE_MESH_H
