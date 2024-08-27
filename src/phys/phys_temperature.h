/// \file
/// \brief Temperature functions.
///
/// Temperature functions.

#ifndef CAESAR_PHYS_TEMPERATURE_H
#define CAESAR_PHYS_TEMPERATURE_H

namespace caesar
{

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

}

#endif // !CAESAR_PHYS_TEMPERATURE_H
