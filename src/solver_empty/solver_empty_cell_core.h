/// \file
/// \brief Empty solver cell core declaration.
///
/// Empty solver cell core declaration.

#ifndef SOLVER_EMPTY_CELL_CORE_H
#define SOLVER_EMPTY_CELL_CORE_H

#include "utils/utils.h"

namespace solver
{

/// \addtogroup solver
/// @{

/// \brief Core of cell.
class CellCore
{

private:

public:

    /// \brief Heat transfer coefficient.
    double htc { 0.0 };

    /// \brief Coefficient of water catching.
    double beta { 0.0 };

    // Constructor.
    CellCore();

    // Destructor.
    virtual
    ~CellCore();

    // Print function.
    friend ostream&
    operator<<(ostream& os,
               const CellCore& a);
};

/// @}

}

#endif // SOLVER_EMPTY_CELL_CORE_H

