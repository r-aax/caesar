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
    load_mesh("./cases/meshes/naca_mz.dat");
    store_mesh("res.dat");
    mesh.print_info();
}

/// \brief Load mesh.
///
/// Load mesh.
///
/// \param[in] fn Name of file.
void
Core::load_mesh(const string& fn)
{
    timer_file.start();
    mesh.load(fn);
    timer_file.stop();
}

/// \brief Store mesh.
///
/// Store mesh.
///
/// \param[in] fn Name of file.
void
Core::store_mesh(const string& fn)
{
    timer_file.start();
    mesh.store(fn);
    timer_file.stop();
}

/// \brief Print timers.
void
Core::print_timers()
{
    cout << "Timers:"
         << " file = " << timer_file.get() << " s,"
         << " calc = " << timer_calc.get() << " s,"
         << " comm = " << timer_comm.get() << " s" << endl;
}

/// @}

}
