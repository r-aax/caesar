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

    /// \brief Temperature.
    double t { 0.0 };

    /// \brief Height of water.
    double hw { 0.0 };

    /// \brief Height of ice.
    double hi { 0.0 };

    /// \brief Heat transfer coefficient.
    double htc { 0.0 };

    /// \brief Coefficient of water catching.
    double beta { 0.0 };

    /// \brief Tau X coordinate.
    double tau_x { 0.0 };

    /// \brief Tau Y coordinate.
    double tau_y { 0.0 };

    /// \brief Tau Z coordiante.
    double tau_z { 0.0 };

    // Constructor.
    CellCore();

    // Destructor.
    virtual
    ~CellCore();

    // Print function.
    friend ostream&
    operator<<(ostream& os,
               const CellCore& a);

    // Get data element.
    double
    get_data_element(const string& name);

    // Set data element.
    void
    set_data_element(const string& name,
                     double value);
};

/// @}

}

#endif // SOLVER_EMPTY_CELL_CORE_H

