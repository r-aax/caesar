/// \file
/// \brief Mesh cell data stub declaration.
///
/// Mesh cell data stub declaration.

#ifndef MESH_CELL_DATA_STUB_H
#define MESH_CELL_DATA_STUB_H

#include "mesh_cell.h"
#include "utils/utils.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Cell data element stub.
///
/// Data element for cell stub.
enum class CellDataElementStub
{
    /// \brief First element.
    First = static_cast<int>(CellElement::Last) + 1,

    /// \brief Stub.
    Stub = First,

    /// \brief Last element.
    Last = Stub
};

/// \brief Cell data.
class CellDataStub
{

public:

    /// \brief Mapper.
    ///
    /// Mapper.
    static utils::Mapper<CellDataElementStub> mapper;

private:

    /// \brief Stub data.
    ///
    /// Stub data.
    double stub { 0.0 };

public:

    //
    // Data access.
    //

    /// \brief Get data from cell.
    ///
    /// Get data from cell.
    ///
    /// \param[in] index Data index.
    ///
    /// \return
    /// Data.
    inline double
    get_element(int index) const
    {
        CellDataElementStub cde { static_cast<CellDataElementStub>(index) };

        // Ignode wrong indices.
        return (cde == CellDataElementStub::Stub) ? stub : 0.0;
    }

    /// \brief Set data to cell.
    ///
    /// Set data to cell.
    ///
    /// \param[in] index Data index.
    /// \param[in] v     Data value.
    inline void
    set_element(int index,
                double v)
    {
        CellDataElementStub cde { static_cast<CellDataElementStub>(index) };

        // Ignore wrong indices.
        if (cde == CellDataElementStub::Stub)
        {
            stub = v;
        }
    }
};

/// @}

}

}

#endif // !MESH_CELL_DATA_STUB_H
