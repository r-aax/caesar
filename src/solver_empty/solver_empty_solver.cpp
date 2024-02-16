/// \file
/// \brief Solver empty implementation.
///
/// Solver empty implementation.

#include "solver_empty_solver.h"

namespace solver
{

/// \addtogroup solver
/// @{

/// \brief Default constructor.
///
/// Default constructor.
Solver::Solver()
{
}

/// \brief Default destructor.
///
/// Default destructor.
Solver::~Solver()
{
}

/// \brief Init solver.
///
/// Init solver.
void
Solver::init()
{
    load_mesh("./cases/meshes/naca_mz.dat");
    store_mesh("res.dat");
    mesh.print_info(cout, true);
}

/// \brief Load mesh.
///
/// Load mesh.
///
/// \param[in] fn Name of file.
void
Solver::load_mesh(const string& fn)
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
Solver::store_mesh(const string& fn)
{
    timer_file.start();
    mesh.store(fn);
    timer_file.stop();
}

/// \brief Print timers.
void
Solver::print_timers()
{
    cout << "Timers:"
         << " file = " << timer_file.get() << " s,"
         << " calc = " << timer_calc.get() << " s,"
         << " comm = " << timer_comm.get() << " s" << endl;
}

/// @}

}
