/// \file
/// \brief Unstructured surface mesh implementation.
///
/// Implementation of unstructured surface mesh.

#include "mesh_unstructured_surface_mesh.h"

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Default constructor.
///
/// Default constructor.
UnstructuredSurfaceMesh::UnstructuredSurfaceMesh()
{
}

/// \brief Default destructor.
///
/// Default destructor.
UnstructuredSurfaceMesh::~UnstructuredSurfaceMesh()
{
}

/// \brief Load mesh.
///
/// Load mesh from file.
///
/// \param fn - Name of file.
void
UnstructuredSurfaceMesh::Load(const string& fn)
{
    cout << "UnstructuredSurfaceMesh::Load : fn = " << fn << endl;
}

/// @}

}
