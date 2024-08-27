/// \file
/// \brief Viscosity functions.
///
/// Viscosity functions.

#include "phys_viscosity.h"

#include "phys_constants.h"
#include "phys_temperature.h"
#include "mth/mth.h"

/// \brief Low temperature guard (C).
#define TEMP_LO_GUARD (-273.15)

/// \brief High temperature guard (C).
#define TEMP_HI_GUARD 1000.0

namespace phys
{

/// \addtogroup phys
/// @{

/// \brief Water dynamic viscosity (Pa * s).
///
/// Interpolation formula (values in Pa * s): \n
/// @f$ \eta =
///     \begin{cases}
///         1.787\cdot10^{-3}, t = 0^{\circ}C \\ \hphantom{}
///         1.519\cdot10^{-3}, t = 5^{\circ}C \\ \hphantom{}
///         1.307\cdot10^{-3}, t = 10^{\circ}C \\ \hphantom{}
///         1.002\cdot10^{-3}, t = 20^{\circ}C \\ \hphantom{}
///         0.798\cdot10^{-3}, t = 30^{\circ}C \\ \hphantom{}
///         0.653\cdot10^{-3}, t = 40^{\circ}C \\ \hphantom{}
///         0.547\cdot10^{-3}, t = 50^{\circ}C \\ \hphantom{}
///         0.467\cdot10^{-3}, t = 60^{\circ}C \\ \hphantom{}
///         0.404\cdot10^{-3}, t = 70^{\circ}C \\ \hphantom{}
///         0.355\cdot10^{-3}, t = 80^{\circ}C \\ \hphantom{}
///         0.315\cdot10^{-3}, t = 90^{\circ}C \\ \hphantom{}
///         0.282\cdot10^{-3}, t = 100^{\circ}C
///     \end{cases} @f$
///
/// \param[in] t Temperature (C).
///
/// \return
/// Water dynamic viscosity (Pa * s).
double
water_dynamic_viscosity(double t)
{

#if (PHYS_USE_INTERPOLATION_FUNCTIONS == 1)

    // Suppress warning.
    (void)t;

    // Take value for cold water.
    return MTH_MILLI * 1.787;

#elif (PHYS_USE_INTERPOLATION_FUNCTIONS == 2)

    static vector<double> ts
    {
        TEMP_LO_GUARD,
        0.0, 5.0, 10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0,
        90.0, 100.0,
        TEMP_HI_GUARD
    };

    static vector<double> dvs
    {
        1.787, // TEMP_LO_GUARD
        1.787, 1.519, 1.307, 1.002, 0.798, 0.653, 0.547, 0.467, 0.404, 0.355,
        0.315, 0.282,
        0.282 // TEMP_HI_GUARD
    };

    double dv = mth::linear_interpolation(ts, dvs, t);

    return MTH_MILLI * dv;

#else

#error "Error in phys::water_dynamic_viscosity compilation."

#endif

}

/// \brief Dynamic air viscosity (Pa * s).
///
/// @f$ \mu = \mu_0 \frac{T_0 + C}{T + C} \left(\frac{T}{T_0}\right)^{\frac{3}{2}} @f$
///
///
/// \param[in] t_celsius Temperature (C).
///
/// \return
/// Ais dynamic viscosity (Pa * s).
double
air_dynamic_viscosity(double t_celsius)
{
    double mu_0 = 18.27 * MTH_MICRO;
    double t_0 = 291.15;
    double c = 120.0;
    double t = celsius_to_kelvin(t_celsius);

    return mu_0 * ((t_0 + c) / (t + c)) * pow(t / t_0, 1.5);
}

/// @}

}
