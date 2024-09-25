/// \file
/// \brief Cell element.
///
/// Cell elements enumeration.

#include "mesh_cell_element.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Cell element mapper.
utils::Mapper<CellElement> CellElementMapper
{
    "cell element",
    vector<string>
    {
        "CellMark", "CellId",
        "Domain", "DistFromBorder",
        "Area",
        "NormalX", "NormalY", "NormalZ"
    }
};

/// @}

}

}
