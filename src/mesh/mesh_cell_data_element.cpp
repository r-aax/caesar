/// \file
/// \brief Cell data element.
///
/// Cell data elements enumeration.

#include "mesh_cell_data_element.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Cell data element mapper.
utils::Mapper<CellDataElement> CellDataElementMapper
{
    "cell data element",
    vector<string>
    {
        "CellMark", "CellId", "Domain",
        "Area",
        "NormalX", "NormalY", "NormalZ",
        "FictitiousNormalX", "FictitiousNormalY", "FictitiousNormalZ"
    }
};

/// @}

}

}
