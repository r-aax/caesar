/// \file
/// \brief Mesh cell data element stub enumeration.
///
/// Mesh cell data element stub enumeration.

#ifndef MESH_CELL_DATA_ELEMENT_STUB_H
#define MESH_CELL_DATA_ELEMENT_STUB_H

#include "mesh_cell_element.h"
#include "utils/utils.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Cell data element stub.
enum class CellDataElementStub
{
    /// \brief First element.
    First = static_cast<int>(CellElement::Last) + 1,

    /// \brief Stub.
    Stub = First,

    /// \brief Last element.
    Last = Stub
};

/// \brief Cell data element mapper stub.
extern utils::Mapper<CellDataElementStub> CellDataElementStubMapper;

/// @}

}

}

#endif // !MESH_CELL_DATA_ELEMENT_STUB_H
