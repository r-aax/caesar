/// \file
/// \brief Phase transitions heat.
///
/// Phase transitions heat.

#include "phys_phase_transition_heat.h"

#include <cassert>

#include "phys_constants.h"
#include "mth/mth.h"

namespace caesar
{

namespace phys
{

/// \addtogroup phys
/// @{

/// \brief Specific vaporization heat (J / kg).
///
/// Interpolation formula (values in Mega Joules / kg): \n
/// @f$ L_{ev} =
///     \begin{cases}
///         2.50, t = 0^{\circ}C \\ \hphantom{}
///         2.47, t = 10^{\circ}C \\ \hphantom{}
///         2.45, t = 20^{\circ}C \\ \hphantom{}
///         2.40, t = 30^{\circ}C \\ \hphantom{}
///         2.38, t = 50^{\circ}C \\ \hphantom{}
///         2.32, t = 70^{\circ}C \\ \hphantom{}
///         2.28, t = 90^{\circ}C \\ \hphantom{}
///         2.26, t = 100^{\circ}C \\ \hphantom{}
///         2.20, t = 120^{\circ}C \\ \hphantom{}
///         2.11, t = 150^{\circ}C \\ \hphantom{}
///         2.01, t = 180^{\circ}C \\ \hphantom{}
///         1.94, t = 200^{\circ}C \\ \hphantom{}
///         1.86, t = 220^{\circ}C \\ \hphantom{}
///         1.70, t = 250^{\circ}C \\ \hphantom{}
///         1.40, t = 300^{\circ}C \\ \hphantom{}
///         0.89, t = 350^{\circ}C \\ \hphantom{}
///         0.44, t = 370^{\circ}C \\ \hphantom{}
///         0.11, t = 374^{\circ}C \\ \hphantom{}
///         0, t = 374,15^{\circ}C
///     \end{cases} @f$
///
/// \param[in] t Temperature (C).
///
/// \return
/// Vaporization heat (J / kg).
double
l_ev(double t)
{

#if (PHYS_USE_INTERPOLATION_FUNCTIONS == 1)

    // Suppress warning.
    (void)t;

    // source:
    // S. Ozgen, M. Canibek.
    // Ice accretion simulation on multi-element airfoils using extended Messinger model.
    return 2.5e+6;

#elif (PHYS_USE_INTERPOLATION_FUNCTIONS == 2)

    static vector<double> ts
    {
        TempLoGuard,
        0.0, 10.0, 20.0, 30.0, 50.0, 70.0, 90.0, 100.0, 120.0, 150.0,
        180.0, 200.0, 220.0, 250.0, 300.0, 350.0, 370.0, 374.0, 374.15,
        TempHiGuard
    };

    // Values in MJ / kg.
    static vector<double> ls
    {
        2.5, // TempLoGuard
        2.5, 2.47, 2.45, 2.4, 2.38, 2.32, 2.28, 2.26, 2.2, 2.11,
        2.01, 1.94, 1.86, 1.7, 1.4, 0.89, 0.44, 0.11, 0.0,
        0.0 // TempHiGuard
    };

    // Obtain values in MJ / kg.
    double l_ev_m = mth::linear_interpolation(ts, ls, t);

    return MTH_MEGA * l_ev_m;

#else

#error "Error in phys::L_ev compilation."

#endif

}

/// \brief Specific sublimation heat (J / kg).
///
/// Interpolation formula (values in kilocalories / kg): \n
/// @f$ L_{su} =
///     \begin{cases}
///         698.4, t = -39^{\circ}C \\ \hphantom{}
///         697.8, t = -38^{\circ}C \\ \hphantom{}
///         697.3, t = -37^{\circ}C \\ \hphantom{}
///         696.8, t = -36^{\circ}C \\ \hphantom{}
///         696.2, t = -35^{\circ}C \\ \hphantom{}
///         695.6, t = -34^{\circ}C \\ \hphantom{}
///         695.1, t = -33^{\circ}C \\ \hphantom{}
///         694.5, t = -32^{\circ}C \\ \hphantom{}
///         694.0, t = -31^{\circ}C \\ \hphantom{}
///         693.4, t = -30^{\circ}C \\ \hphantom{}
///         692.9, t = -29^{\circ}C \\ \hphantom{}
///         692.3, t = -28^{\circ}C \\ \hphantom{}
///         691.8, t = -27^{\circ}C \\ \hphantom{}
///         691.2, t = -26^{\circ}C \\ \hphantom{}
///         690.6, t = -25^{\circ}C \\ \hphantom{}
///         690.0, t = -24^{\circ}C \\ \hphantom{}
///         689.5, t = -23^{\circ}C \\ \hphantom{}
///         688.9, t = -22^{\circ}C \\ \hphantom{}
///         688.6, t = -21^{\circ}C \\ \hphantom{}
///         688.1, t = -20^{\circ}C \\ \hphantom{}
///         687.6, t = -19^{\circ}C \\ \hphantom{}
///         687.0, t = -18^{\circ}C \\ \hphantom{}
///         686.5, t = -17^{\circ}C \\ \hphantom{}
///         685.9, t = -16^{\circ}C \\ \hphantom{}
///         685.3, t = -15^{\circ}C \\ \hphantom{}
///         684.7, t = -14^{\circ}C \\ \hphantom{}
///         684.2, t = -13^{\circ}C \\ \hphantom{}
///         683.6, t = -12^{\circ}C \\ \hphantom{}
///         683.1, t = -11^{\circ}C \\ \hphantom{}
///         682.5, t = -10^{\circ}C \\ \hphantom{}
///         681.9, t = -9^{\circ}C \\ \hphantom{}
///         681.4, t = -8^{\circ}C \\ \hphantom{}
///         680.8, t = -7^{\circ}C \\ \hphantom{}
///         680.3, t = -6^{\circ}C \\ \hphantom{}
///         679.7, t = -5^{\circ}C \\ \hphantom{}
///         679.1, t = -4^{\circ}C \\ \hphantom{}
///         678.5, t = -3^{\circ}C \\ \hphantom{}
///         678.0, t = -2^{\circ}C \\ \hphantom{}
///         677.6, t = -1^{\circ}C \\ \hphantom{}
///         676.9, t = 0^{\circ}C \\ \hphantom{}
///     \end{cases} @f$
///
/// \param[in] t Temperature (C).
///
/// \return
/// Specific sublimation heat (J / kg).
double
l_su(double t)
{

#if (PHYS_USE_INTERPOLATION_FUNCTIONS == 1)

    // Suppress warning.
    (void)t;

    // source:
    // S. Ozgen, M. Canibek.
    // Ice accretion simulation on multi-element airfoils using extended Messinger model.
    return 2.8344e+6;

#elif (PHYS_USE_INTERPOLATION_FUNCTIONS == 2)

    static vector<double> ts
    {
        TempLoGuard,
        -39.0, -38.0, -37.0, -36.0, -35.0, -34.0, -33.0, -32.0, -31.0, -30.0,
        -29.0, -28.0, -27.0, -26.0, -25.0, -24.0, -23.0, -22.0, -21.0, -20.0,
        -19.0, -18.0, -17.0, -16.0, -15.0, -14.0, -13.0, -12.0, -11.0, -10.0,
        -9.0, -8.0, -7.0, -6.0, -5.0, -4.0, -3.0, -2.0, -1.0, 0.0,
        TempHiGuard
    };

    // Values in kcal / kg.
    static vector<double> su
    {
        698.4, // TempLoGuard
        698.4, 697.8, 697.3, 696.8, 696.2, 695.6, 695.1, 694.5, 694.0, 693.4,
        692.9, 692.3, 691.8, 691.2, 690.6, 690.0, 689.5, 688.9, 688.6, 688.1,
        687.6, 687.0, 686.5, 685.9, 685.3, 684.7, 684.2, 683.6, 683.1, 682.5,
        681.9, 681.4, 680.8, 680.3, 679.7, 679.1, 678.5, 678.0, 677.6, 676.9,
        676.9 // TempHiGuard
    };

    // Obtain values in kcal / kg.
    double l_su_kk = mth::linear_interpolation(ts, su, t);

    return KilocalorieJoules * l_su_kk;

#else

#error "Error in phys::L_su compilation."

#endif

}

/// @}

}

}
