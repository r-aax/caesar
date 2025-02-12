/// \file
/// \brief Heat conductivity functions.
///
/// Heat conductivity functions.

#ifndef CAESAR_PHYS_HEAT_CONDUCTIVITY_H
#define CAESAR_PHYS_HEAT_CONDUCTIVITY_H

namespace caesar
{

namespace phys
{

/// \addtogroup phys
/// @{

/// \brief Water thermal conductivity (W / (m * degree)).
///
/// Water thermal conductivity (W / (m * degree)).
const double WaterThermalConductivity = 0.56;

/// \brief Ice thermal conductivity (W / (m * degree)).
///
/// Ice thermal conductivity (W / (m * degree)).
const double IceThermalConductivity = 2.22;

// Heat flux (J / (m^2 * s)).
double
heat_flux(double lambda,
          double width,
          double t_from,
          double t_to);

/// @}

}

}

#endif // !CAESAR_PHYS_HEAT_CONDUCTIVITY_H
