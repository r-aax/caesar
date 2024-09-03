/// \file
/// \brief Class that holds cells.
///
/// Class that holds cells.

#ifndef CAESAR_MESH_CELLS_HOLDER_H
#define CAESAR_MESH_CELLS_HOLDER_H

#include <vector>

using namespace std;

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

class Cell;

/// \brief Class that holds cells
///
/// Class that holds cells.
class CellsHolder
{

private:

    /// \brief Vector of cells pointers.
    vector<Cell*> cells_;

public:

    /// \brief Get cells (const version).
    ///
    /// Get cells (const verstion).
    ///
    /// \return
    /// Cells (const version).
    inline const vector<Cell*>&
    cells() const
    {
        return cells_;
    }

    /// \brief Get cells.
    ///
    /// Get cells.
    ///
    /// \return
    /// Cells.
    inline vector<Cell*>&
    cells()
    {
        return cells_;
    }

    /// \brief Get count of cells.
    ///
    /// Get count of cells.
    ///
    /// \return
    /// Count of cells.
    inline size_t
    cells_count() const
    {
        return cells_.size();
    }

    /// \brief Add cell.
    ///
    /// Add cell.
    ///
    /// \param[in] c Cell pointer.
    inline void
    add_cell(Cell* c)
    {
        cells_.push_back(c);
    }

    /// \brief Clear.
    ///
    /// Clear all elements.
    inline void
    clear_cells()
    {
        cells_.clear();
    }

    /// \brief Get cell (const version).
    ///
    /// Get cell (const version).
    ///
    /// \param[in] i Index of cell.
    ///
    /// \return
    /// Pointer to cell (const version).
    inline const Cell*
    cell(size_t i) const
    {
        return cells_[i];
    }

    /// \brief Get cell.
    ///
    /// Get cell.
    ///
    /// \param[in] i Index of cell.
    ///
    /// \return
    /// Pointer to cell.
    inline Cell*
    cell(size_t i)
    {
        return cells_[i];
    }
};

/// @}

}

}

#endif // !CAESAR_MESH_CELLS_HOLDER_H
