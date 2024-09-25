/// \file
/// \brief Cell elements enumeration.
///
/// Cell elements enumeration.

#ifndef CAESAR_MESH_CELL_ELEMENT_H
#define CAESAR_MESH_CELL_ELEMENT_H

#include "utils/utils.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Cell element.
enum class CellElement
{
    /// \brief First element.
    First = 0,

    /// \brief Cell mark (for technical use).
    CellMark = First,

    /// \brief Cell identifier.
    CellId,

    /// \brief Domain number.
    Domain,

    /// \brief Distance from border.
    DistFromBorder,

    /// \brief Area (m^2).
    Area,

    /// \brief Normal X component.
    NormalX,

    /// \brief Normal Y component.
    NormalY,

    /// \brief Normal Z component.
    NormalZ,

    /// \brief Last element.
    Last = NormalZ
};

/// \brief Cell data element mapper.
extern utils::Mapper<CellElement> CellElementMapper;

/// @}

}

}

#endif // !CAESAR_MESH_CELL_ELEMENT_H
