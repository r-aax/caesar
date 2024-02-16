/// \file
/// \brief Core of solver empty implementation.
///
/// Core of solver empty implementation.

#include "solver_empty_core.h"

namespace solver
{

/// \addtogroup solver
/// @{

/// \brief Default constructor.
///
/// Default constructor.
Core::Core()
{
}

/// \brief Default destructor.
///
/// Default destructor.
Core::~Core()
{
}

/// \brief Init solver core.
///
/// Init solver core.
void
Core::init()
{
    mesh.load("./cases/meshes/naca_mz.dat");
    mesh.store("res.dat");
    mesh.print_info();
}

/// @}

}
