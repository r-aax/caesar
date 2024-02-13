/// \file
/// \brief Empty solver cell atom declaration.
///
/// Empty solver cell atom declaration.

#ifndef SOLVER_EMPTY_CELL_ATOM_H
#define SOLVER_EMPTY_CELL_ATOM_H

#include "utils/utils.h"

namespace solver
{

/// \addtogroup solver
/// @{

/// \brief Atom of cell.
class CellAtom
{

private:

public:

    /// \brief Heat transfer coefficient.
    double htc { 0.0 };

    /// \brief Coefficient of water catching.
    double beta { 0.0 };

    // Constructor.
    CellAtom();

    // Destructor.
    ~CellAtom();

    // Print function.
    friend ostream&
    operator<<(ostream& os,
               const CellAtom& a);
};

/// @}

}

#endif // SOLVER_EMPTY_CELL_ATOM_H

