/// \file
/// \brier Core of solver empty.
///
/// Core of solver empty.

#ifndef SOLVER_EMPTY_CORE_H
#define SOLVER_EMPTY_CORE_H

#include "mesh/mesh.h"

namespace solver
{

/// \addtogroup solver
/// @{

/// \brief Core of solver.
class Core
{

private:

    /// \brief Mesh.
    mesh::UnstructuredSurfaceMesh mesh;

public:

    // Default constructor.
    Core();

    // Default destructor.
    ~Core();

    // Init solver core.
    void
    init();
};

/// @}

}

#endif // SOLVER_EMPTY_CORE_H
