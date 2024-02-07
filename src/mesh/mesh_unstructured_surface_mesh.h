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

class UnstructuredSurfaceMesh
{

private:

public:

    // Constructor.
    UnstructuredSurfaceMesh();

    // Destructor.
    ~UnstructuredSurfaceMesh();

    // Load.
    void
    Load(const string& fn);
};

/// @}

}

#endif // MESH_UNSTRUCTURED_SURFACE_MESH_H
