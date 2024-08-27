/// \file
/// \brief Heat transition phases functions.
///
/// Heat transition phases functions.

#ifndef PHYS_PHASE_TRANSITION_HEAT_H
#define PHYS_PHASE_TRANSITION_HEAT_H

namespace phys
{

/// \addtogroup phys
/// @{

/// \brief Specific soldification heat (J / kg).
const double L_fus = 332400.0;

/// \brief Water thermal conductivity (W / (m * degree)).
const double WaterThermalConductivity = 0.56;

/// \brief Ice thermal conductivity (W / (m * degree)).
const double IceThermalConductivity = 2.22;

// Vaporization heat (J / kg).
double
l_ev(double t);

// Sublimation heat (J / kg).
double
l_su(double t);

/// @}

}

#endif // !PHYS_PHASE_TRANSITION_HEAT_H
