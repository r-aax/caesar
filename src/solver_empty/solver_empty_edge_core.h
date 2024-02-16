/// \file
/// \brief Empty solver edge core declaration.
///
/// Empty solver edge core declaration.

#ifndef SOLVER_EMPTY_EDGE_CORE_H
#define SOLVER_EMPTY_EDGE_CORE_H

#include "utils/utils.h"

namespace solver
{

/// \addtogroup solver
/// @{

/// \brief Core of edge.
class EdgeCore
{

private:

public:

    // Constructor.
    EdgeCore();

    // Destructor.
    virtual
    ~EdgeCore();

    // Print function.
    friend ostream&
    operator<<(ostream& os,
               const EdgeCore& a);
};

/// @}

}

#endif // SOLVER_EMPTY_EDGE_CORE_H
