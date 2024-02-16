/// \file
/// \brief Main file.
///
/// This file contains entry point to CAEsar module.

#include "caesar.h"

int
main()
{
    solver::Solver solver;

    solver.init();
    solver.print_timers();

    return 0;
}
