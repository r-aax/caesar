/// \file
/// \brief Mesh cell data stub declaration.
///
/// Mesh cell data stub declaration.

#include "mesh_cell_data_stub.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

// Mapper initialization.
utils::Mapper<CellDataElementStub> CellDataStub::mapper
{
    "mesh cell data element stub",
    vector<string>
    {
        "Stub"
    }
};

/// @}

}

}
