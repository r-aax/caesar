/// \file
/// \brief Heat conductivity functions.
///
/// Heat conductivity functions.

#include "phys_heat_conductivity.h"

namespace caesar
{

namespace phys
{

/// \addtogroup phys
/// @{

/// \brief Heat flux (J / (m^2 * s)).
///
/// Heat flux.
///
/// @f$ Q = \frac{\lambda}{w} (t_{from} - t_{to}) @f$
///
/// \param[in] lambda Conductivity coefficient (W / (m * degree)).
/// \param[in] width  Width (m).
/// \param[in] t_from From temperature (C).
/// \param[in] t_to   To temperature (C).
///
/// \return
/// Heat flux (J / (m^2 * s)).
double
heat_flux(double lambda,
          double width,
          double t_from,
          double t_to)
{
    return (lambda / width) * (t_from - t_to);
}

/// @}

}

}
