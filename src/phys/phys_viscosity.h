/// \file
/// \brief Viscosity functions.
///
/// Viscosity functions.

#ifndef PHYS_VISCOSITY_H
#define PHYS_VISCOSITY_H

namespace phys
{

/// \addtogroup phys
/// @{

// Water dynamic viscosity.
double
water_dynamic_viscosity(double t);

// Air dynamic viscosity.
double
air_dynamic_viscosity(double t);

/// @}

}

#endif // !PHYS_VISCOSITY_H
