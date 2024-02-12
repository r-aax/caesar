/// \file
/// \brief Empty solver edge atom declaration.
///
/// Empty solver edge atom declaration.

#ifndef SOLVER_EMPTY_EDGE_ATOM_H
#define SOLVER_EMPTY_EDGE_ATOM_H

#include "utils/utils.h"

namespace solver
{

/// \addtogroup solver
/// @{

/// \brief Atom of edge.
class EdgeAtom
{

private:

public:

    // Constructor.
    EdgeAtom();

    // Destructor.
    ~EdgeAtom();

    // Print function.
    friend ostream&
    operator<<(ostream& os,
               const EdgeAtom& a);
};

/// @}

}

#endif // SOLVER_EMPTY_EDGE_ATOM_H
