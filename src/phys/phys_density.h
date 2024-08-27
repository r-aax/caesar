/// \file
/// \brief Density functions.
///
/// Density functions.

#ifndef CAESAR_PHYS_DENSITY_H
#define CAESAR_PHYS_DENSITY_H

namespace caesar
{

namespace phys
{

/// \addtogroup phys
/// @{

/// \brief Water density (kg / m^3).
const double Rho_w = 1000.0;

/// \brief Ice density (kg / m^3).
///
/// source:
/// S. Ozgen, M. Canibek.
/// Ice accretion simulation on multi-element airfoils using extended Messinger model.
const double Rho_i = 917.0;

// Air density (kg / (m^3)).
double
rho_a(double t,
      double p);

/// @}

}

}

#endif // !CAESAR_PHYS_DENSITY_H
