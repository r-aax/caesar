/// \file
/// \brief Main file.
///
/// This file contains entry point.

#include "solver/solver.h"

int
main()
{
    solver::Solver solver;

    solver.init();
    solver.print_timers();

    return 0;
}
