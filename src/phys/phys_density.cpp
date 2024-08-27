/// \file
/// \brief Density functions.
///
/// Density functions.

#include "phys_density.h"

#include "phys_constants.h"
#include "phys_temperature.h"

namespace caesar
{

namespace phys
{

/// \addtogroup phys
/// @{

/// \brief Air pressure (kg / (m^3)).
///
/// Mendeleev-Clapeyron equation. \n
/// @f$ \rho = \frac{pM}{RT} @f$, \n
/// p - pressure, \n
/// M - molar mass of dry air (29 g/mol), \n
/// R - universal gas constant, \n
/// T - temperature (K).
///
/// \param[in] t Temperature (C).
/// \param[in] p Pressure (Pa).
///
/// \return
/// Air density (kg / m^3).
double
rho_a(double t,
      double p)
{
    const double mm = 29.0 * 1.0e-3;
    double tk = celsius_to_kelvin(t);

    return (p * mm) / (MolarGasConstant * tk);
}

/// @}

}

}
