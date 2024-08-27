/// \file
/// \brief Physiscal constants.
///
/// Physical constants.

#ifndef CAESAR_PHYS_CONSTANTS_H
#define CAESAR_PHYS_CONSTANTS_H

/// \addtogroup phys
/// @{

/// \brief Use interpolation functions.
///
/// - 1 - do not use,
/// - 2 - use
#define PHYS_USE_INTERPOLATION_FUNCTIONS 2

/// @}

namespace caesar
{

namespace phys
{

/// \addtogroup phys
/// @{

//
// Fundamental constants.
//

/// \brief Gravitational acceleration (m / s^2).
const double GravitationalAcceleration = 9.80665;

/// \brief Stefano-Boltzmann constant (W / (m^2 * K^4)).
///
/// Proportional coefficient in Stefano-Boltzmann law.
const double StefanBoltzmannConstant = 5.670374419e-8;

/// \brief Universal gas constants (J / (mol * K)).
const double MolarGasConstant = 8.31446261815324;

//
// Different measure units relations.
//

/// \brief Joules count in one kilicalorie (J).
const double KilocalorieJoules = 4186.8;

/// \brief Kilocalories count in one Joule (kcal).
const double JouleKilocalories = (1.0 / KilocalorieJoules);

//
// Other constants.
//

/// \brief Water tension coefficient (N / m).
///
/// 75,6 * 10^(-3) (N / m).
const double WaterSurfaceTensionCoefficient = 0.0756;

/// @}

}

}

#endif // !CAESAR_PHYS_CONSTANTS_H
