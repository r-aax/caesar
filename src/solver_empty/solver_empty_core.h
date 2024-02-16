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
    mesh::Mesh mesh;

    /// \brief Timer for files.
    utils::Timer timer_file;

    /// \brief Timer for calculations.
    utils::Timer timer_calc;

    /// \brief Timer for communications.
    utils::Timer timer_comm;

public:

    // Default constructor.
    Core();

    // Default destructor.
    ~Core();

    // Init solver core.
    void
    init();

    // Load mesh.
    void
    load_mesh(const string& fn);

    // Store mesh.
    void
    store_mesh(const string& fn);

    // Print timers.
    void
    print_timers();
};

/// @}

}

#endif // SOLVER_EMPTY_CORE_H
