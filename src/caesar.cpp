/// \file
/// \brief Main file.
///
/// This file contains entry point to CAEsar module.

#include "caesar.h"

int
main()
{
    solver::Core core;

    core.init();
    core.print_timers();

    return 0;
}
