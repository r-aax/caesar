/// \file
/// \brief Heat capacity functions.
///
/// Heat capacity functions.

#ifndef PHYS_HEAT_CAPACITY_H
#define PHYS_HEAT_CAPACITY_H

namespace phys
{

/// \addtogroup phys
/// @{

// Water heat capacity (J / (kg * degree)).
double
cp_w(double t);

// Ice heat capacity (J / (kg * degree)).
double
cp_i(double t);

// Air heat capacity (J / (kg * degree)).
double
cp_a(double t);

/// @}

}

#endif // !PHYS_HEAT_CAPACITY_H
