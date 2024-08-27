/// \file
/// \brief Temperature functions.
///
/// Temperature functions.

#ifndef PHYS_TEMPERATURE_H
#define PHYS_TEMPERATURE_H

namespace phys
{

/// \addtogroup phys
/// @{

/// \brief Absolute zero (Celsius).
const double AbsoluteZero  = -273.15;

// Transform Celsius (C) to Kelvins (K).
double
celsius_to_kelvin(double tc);

// Transform Kelvins (K) to Celsius (C).
double
kelvin_to_celsius(double tk);

/// @}

}

#endif // !PHYS_TEMPERATURE_H
