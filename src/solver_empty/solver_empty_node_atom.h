/// \file
/// \brief Empty solver node atom declaration.
///
/// Empty solver node atom declaration.

#ifndef SOLVER_EMPTY_NODE_ATOM_H
#define SOLVER_EMPTY_NODE_ATOM_H

#include "utils/utils.h"

namespace solver
{

/// \addtogroup solver
/// @{

/// \brief Atom of node.
class NodeAtom
{

private:

public:

    // Constructor.
    NodeAtom();

    // Destructor.
    ~NodeAtom();

    // Print function.
    friend ostream&
    operator<<(ostream& os,
               const NodeAtom& a);
};

/// @}

}

#endif // SOLVER_EMPTY_NODE_ATOM_H
