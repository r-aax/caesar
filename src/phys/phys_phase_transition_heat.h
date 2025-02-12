/// \file
/// \brief Heat transition phases functions.
///
/// Heat transition phases functions.

#ifndef CAESAR_PHYS_PHASE_TRANSITION_HEAT_H
#define CAESAR_PHYS_PHASE_TRANSITION_HEAT_H

namespace caesar
{

namespace phys
{

/// \addtogroup phys
/// @{

/// \brief Specific soldification heat (J / kg).
const double L_fus = 332400.0;

// Vaporization heat (J / kg).
double
l_ev(double t);

// Sublimation heat (J / kg).
double
l_su(double t);

/// @}

}

}

#endif // !CAESAR_PHYS_PHASE_TRANSITION_HEAT_H
