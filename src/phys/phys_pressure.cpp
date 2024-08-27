/// \file
/// \brief Pressure functions.
///
/// Pressure functions.

#include "phys_pressure.h"

namespace phys
{

/// \addtogroup phys
/// @{

/// \brief Water vapor pressure (Pa).
///
/// @f$ p_v = 3386.0 \times (0.0039 + 6.8096 \times 10^{-6} \times T_v^2
///                          + 3.5579 \times 10^{-7} \times T_v^3) @f$
///
/// @f$ T_v = 72.0 + 1.8 \times T @f$
///
/// \param[in] t Temperature (C).
///
/// \return
/// Water vapor pressure (Pa).
double
water_vapor_pressure(double t)
{
    double t_v = 72.0 + 1.8 * t;
    double p_v = 3386.0 * (0.0039
                           + 6.8096e-6 * t_v * t_v
                           + 3.5579e-7 * t_v * t_v * t_v);

    return p_v;
}

/// @}

}
