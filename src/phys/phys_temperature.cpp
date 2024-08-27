/// \file
/// \brief Temperature functions.
///
/// Temperature functions.

#include "phys_temperature.h"

namespace caesar
{

namespace phys
{

/// \addtogroup phys
/// @{

/// \brief Transform Celsius (C) to Kelvins (K).
///
/// \param[in] tc Temperature (C).
///
/// \return
/// Temperature (K).
double
celsius_to_kelvin(double tc)
{
    return tc - AbsoluteZero;
}

/// \brief Transform Kelvins (K) to Celsius (C).
///
/// \param[in] tk Temperature (K).
///
/// \return
/// Temperature (C).
double
kelvin_to_celsius(double tk)
{
    return tk + AbsoluteZero;
}

/// @}

}

}
