/// \file
/// \brief Viscosity functions.
///
/// Viscosity functions.

#ifndef CAESAR_PHYS_VISCOSITY_H
#define CAESAR_PHYS_VISCOSITY_H

namespace caesar
{

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

}

#endif // !CAESAR_PHYS_VISCOSITY_H
