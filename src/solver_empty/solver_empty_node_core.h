/// \file
/// \brief Empty solver node core declaration.
///
/// Empty solver node core declaration.

#ifndef SOLVER_EMPTY_NODE_CORE_H
#define SOLVER_EMPTY_NODE_CORE_H

#include "utils/utils.h"

namespace solver
{

/// \addtogroup solver
/// @{

/// \brief Core of node.
class NodeCore
{

private:

public:

    // Constructor.
    NodeCore();

    // Destructor.
    virtual
    ~NodeCore();

    // Print function.
    friend ostream&
    operator<<(ostream& os,
               const NodeCore& a);
};

/// @}

}

#endif // SOLVER_EMPTY_NODE_CORE_H
