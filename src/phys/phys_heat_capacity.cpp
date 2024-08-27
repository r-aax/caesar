/// \file
/// \brief Heat capacity functions.
///
/// Heat capacity functions.

#include "phys_heat_capacity.h"

#include <cassert>

#include "phys_constants.h"
#include "mth/mth.h"

/// \brief Low temperature guard (C).
#define TEMP_LO_GUARD (-273.15)

/// \brief High temperature guard (C).
#define TEMP_HI_GUARD 1000.0

namespace caesar
{

namespace phys
{

/// \addtogroup phys
/// @{

/// \brief Water heat capacity (J / (kg * degree)).
///
/// Interpolation formula (values in (calories / (gramm * degree))): \n
/// @f$ C{p,w} =
///     \begin{cases}
///         1.019, t = -9^{\circ}C \\ \hphantom{}
///         1.018, t = -8^{\circ}C \\ \hphantom{}
///         1.017, t = -7^{\circ}C \\ \hphantom{}
///         1.016, t = -6^{\circ}C \\ \hphantom{}
///         1.015, t = -5^{\circ}C \\ \hphantom{}
///         1.014, t = -4^{\circ}C \\ \hphantom{}
///         1.013, t = -3^{\circ}C \\ \hphantom{}
///         1.012, t = -2^{\circ}C \\ \hphantom{}
///         1.011, t = -1^{\circ}C \\ \hphantom{}
///         1.01, t = 0^{\circ}C \\ \hphantom{}
///         1.009, t = 1^{\circ}C \\ \hphantom{}
///         1.008, t = 2^{\circ}C \\ \hphantom{}
///         1.008, t = 3^{\circ}C \\ \hphantom{}
///         1.007, t = 4^{\circ}C \\ \hphantom{}
///         1.006, t = 5^{\circ}C \\ \hphantom{}
///         1.005, t = 6^{\circ}C \\ \hphantom{}
///         1.004, t = 7^{\circ}C \\ \hphantom{}
///         1.004, t = 9^{\circ}C \\ \hphantom{}
///         1.003, t = 10^{\circ}C \\ \hphantom{}
///         1.003, t = 11^{\circ}C \\ \hphantom{}
///         1.002, t = 12^{\circ}C \\ \hphantom{}
///         1.002, t = 14^{\circ}C \\ \hphantom{}
///         1.001, t = 15^{\circ}C \\ \hphantom{}
///         1.001, t = 17^{\circ}C \\ \hphantom{}
///         1.0, t = 18^{\circ}C \\ \hphantom{}
///         1.0, t = 22^{\circ}C \\ \hphantom{}
///         0.999, t = 23^{\circ}C \\ \hphantom{}
///         0.999, t = 29^{\circ}C
///     \end{cases} @f$
///
/// \param[in] t Temperature (C).
///
/// \return
/// Water heat capacity (J / (kg * degree)).
double
cp_w(double t)
{

#if (PHYS_USE_INTERPOLATION_FUNCTIONS == 1)

    // Suppress warning.
    (void)t;

    // source:
    // S. Ozgen, M. Canibek.
    // Ice accretion simulation on multi-element airfoils using extended Messinger model.
    return 4218.0;

#elif (PHYS_USE_INTERPOLATION_FUNCTIONS == 2)

    static vector<double> ts
    {
        TEMP_LO_GUARD,
        -9.0, -8.0, -7.0, -6.0, -5.0, -4.0, -3.0, -2.0, -1.0, 0.0,
        1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 9.0, 10.0, 11.0,
        12.0, 14.0, 15.0, 17.0, 18.0, 22.0, 23.0, 29.0,
        TEMP_HI_GUARD
    };

    // Values in cal / (g * degree).
    static vector<double> cps
    {
        1.019, // TEMP_LO_GUARD
        1.019, 1.018, 1.017, 1.016, 1.015, 1.014, 1.013, 1.012, 1.011, 1.01,
        1.009, 1.008, 1.008, 1.007, 1.006, 1.005, 1.004, 1.004, 1.003, 1.003,
        1.002, 1.002, 1.001, 1.001, 1.0, 1.0, 0.999, 0.999,
        0.999 // TEMP_HI_GUARD
    };

    // Obtain value in cal / (g * degree).
    double cp_w = mth::linear_interpolation(ts, cps, t);

    // cal / (g * degree) = kcal / (kg * degree) = KilocalorieJoules * J / (kg * degree).
    return KilocalorieJoules * cp_w;

#else

#error "Error in phys::Cp_w compilation."

#endif

}

/// \brief Ice heat capacity (J / (kg * degree)).
///
/// Interpolation formula (values in (calories / (gramm * degree))): \n
/// @f$ C{p,ice} =
///     \begin{cases}
///         0.452, t = -28^{\circ}C \\ \hphantom{}
///         0.454, t = -27^{\circ}C \\ \hphantom{}
///         0.455, t = -26^{\circ}C \\ \hphantom{}
///         0.457, t = -25^{\circ}C \\ \hphantom{}
///         0.459, t = -24^{\circ}C \\ \hphantom{}
///         0.461, t = -23^{\circ}C \\ \hphantom{}
///         0.463, t = -22^{\circ}C \\ \hphantom{}
///         0.466, t = -21^{\circ}C \\ \hphantom{}
///         0.467, t = -20^{\circ}C \\ \hphantom{}
///         0.468, t = -19^{\circ}C \\ \hphantom{}
///         0.470, t = -18^{\circ}C \\ \hphantom{}
///         0.472, t = -17^{\circ}C \\ \hphantom{}
///         0.474, t = -16^{\circ}C \\ \hphantom{}
///         0.476, t = -15^{\circ}C \\ \hphantom{}
///         0.478, t = -14^{\circ}C \\ \hphantom{}
///         0.480, t = -13^{\circ}C \\ \hphantom{}
///         0.481, t = -12^{\circ}C \\ \hphantom{}
///         0.483, t = -11^{\circ}C \\ \hphantom{}
///         0.485, t = -10^{\circ}C
///     \end{cases} @f$
///
/// \param[in] t Temperature (C).
///
/// \return
/// Ice heat capacity (J / (kg * degree)).
double
cp_i(double t)
{

#if (PHYS_USE_INTERPOLATION_FUNCTIONS == 1)

    // Suppress warning.
    (void)t;

    // source:
    // S. Ozgen, M. Canibek.
    // Ice accretion simulation on multi-element airfoils using extended Messinger model.
    return 2050.0;

#elif (PHYS_USE_INTERPOLATION_FUNCTIONS == 2)

    static vector<double> ts
    {
        TEMP_LO_GUARD,
        -28.0, -27.0, -26.0, -25.0, -24.0, -23.0, -22.0, -21.0, -20.0, -19.0,
        -18.0, -17.0, -16.0, -15.0, -14.0, -13.0, -12.0, -11.0, -10.0,
        TEMP_HI_GUARD
    };

    // Valus in cal / (g * degree).
    static vector<double> cps
    {
        0.452, // TEMP_LO_GUARD
        0.452, 0.454, 0.455, 0.457, 0.459, 0.461, 0.463, 0.466, 0.467, 0.468,
        0.470, 0.472, 0.474, 0.476, 0.478, 0.480, 0.481, 0.483, 0.485,
        0.485 // TEMP_HI_GUARD
    };

    // Obtain value in cal / (g * degree).
    double cp_ice = mth::linear_interpolation(ts, cps, t);

    // cal / (g * degree) = kcal / (kg * degree) = KilocalorieJoules * J / (kg * degree).
    return KilocalorieJoules * cp_ice;

#else

#error "Error in phys::Cp_i compilation."

#endif

}

/// \brief Air heat capacity (J / (kg * degree)).
///
/// Interpolation formula (values in (J / (kg * degree))): \n
/// @f$ C{p,a} =
///     \begin{cases}
///         1013.0, t = -50^{\circ}C \\ \hphantom{}
///         1013.0, t = -45^{\circ}C \\ \hphantom{}
///         1013.0, t = -40^{\circ}C \\ \hphantom{}
///         1013.0, t = -35^{\circ}C \\ \hphantom{}
///         1013.0, t = -30^{\circ}C \\ \hphantom{}
///         1011.0, t = -25^{\circ}C \\ \hphantom{}
///         1009.0, t = -20^{\circ}C \\ \hphantom{}
///         1009.0, t = -15^{\circ}C \\ \hphantom{}
///         1009.0, t = -10^{\circ}C \\ \hphantom{}
///         1007.0, t = -5^{\circ}C \\ \hphantom{}
///         1005.0, t = 0^{\circ}C \\ \hphantom{}
///         1005.0, t = 10^{\circ}C \\ \hphantom{}
///         1005.0, t = 15^{\circ}C \\ \hphantom{}
///         1005.0, t = 20^{\circ}C \\ \hphantom{}
///         1005.0, t = 30^{\circ}C \\ \hphantom{}
///         1005.0, t = 40^{\circ}C \\ \hphantom{}
///         1005.0, t = 50^{\circ}C \\ \hphantom{}
///         1005.0, t = 60^{\circ}C \\ \hphantom{}
///         1009.0, t = 70^{\circ}C \\ \hphantom{}
///         1009.0, t = 80^{\circ}C \\ \hphantom{}
///         1009.0, t = 90^{\circ}C \\ \hphantom{}
///         1009.0, t = 100^{\circ}C \\ \hphantom{}
///         1009.0, t = 110^{\circ}C \\ \hphantom{}
///         1009.0, t = 120^{\circ}C \\ \hphantom{}
///         1011.0, t = 130^{\circ}C \\ \hphantom{}
///         1013.0, t = 140^{\circ}C \\ \hphantom{}
///         1015.0, t = 150^{\circ}C \\ \hphantom{}
///         1017.0, t = 160^{\circ}C \\ \hphantom{}
///         1020.0, t = 170^{\circ}C \\ \hphantom{}
///         1022.0, t = 180^{\circ}C \\ \hphantom{}
///         1024.0, t = 190^{\circ}C \\ \hphantom{}
///         1026.0, t = 200^{\circ}C \\ \hphantom{}
///         1037.0, t = 250^{\circ}C \\ \hphantom{}
///         1047.0, t = 300^{\circ}C \\ \hphantom{}
///         1058.0, t = 350^{\circ}C \\ \hphantom{}
///         1068.0, t = 400^{\circ}C \\ \hphantom{}
///         1081.0, t = 450^{\circ}C \\ \hphantom{}
///         1093.0, t = 500^{\circ}C \\ \hphantom{}
///         1104.0, t = 550^{\circ}C
///     \end{cases} @f$
///
/// \param[in] t Temperature (C)
///
/// \return
/// Air heat capacity (J / (kg * degree)).
double
cp_a(double t)
{

#if (PHYS_USE_INTERPOLATION_FUNCTIONS == 1)

    // Suppress warning.
    (void)t;

    // source:
    // S. Ozgen, M. Canibek.
    // Ice accretion simulation on multi-element airfoils using extended Messinger model.
    return 1006.0;

#elif (PHYS_USE_INTERPOLATION_FUNCTIONS == 2)

    static vector<double> ts
    {
        TEMP_LO_GUARD,
        -50.0, -45.0, -40.0, -35.0, -30.0, -25.0, -20.0, -15.0, -10.0,  -5.0,
        0.0, 10.0, 15.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0,
        90.0, 100.0, 110.0, 120.0, 130.0, 140.0, 150.0, 160.0, 170.0, 180.0,
        190.0, 200.0, 250.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0,
        TEMP_HI_GUARD
    };

    // Values in J / (kg * degree).
    static vector<double> cps
    {
        1013.0, // TEMP_LO_GUARD
        1013.0, 1013.0, 1013.0, 1013.0, 1013.0, 1011.0, 1009.0, 1009.0, 1009.0, 1007.0,
        1005.0, 1005.0, 1005.0, 1005.0, 1005.0, 1005.0, 1005.0, 1005.0, 1009.0, 1009.0,
        1009.0, 1009.0, 1009.0, 1009.0, 1011.0, 1013.0, 1015.0, 1017.0, 1020.0, 1022.0,
        1024.0, 1026.0, 1037.0, 1047.0, 1058.0, 1068.0, 1081.0, 1093.0, 1104.0,
        1104.0 // TEMP_HI_GUARD
    };

    // Obtain values in J / (kg * degree).
    double cp_a = mth::linear_interpolation(ts, cps, t);

    return cp_a;

#else

#error "Error in phys::Cp_a compilation."

#endif

}

/// @}

}

}
