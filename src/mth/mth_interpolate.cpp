/// \file
/// \brief Interpolation implementation.
///
/// Implementation of interpolation, extrapolation, addition definition, etc.

#include "mth_interpolate.h"

#include "mth_basics.h"
#include "diag/diag.h"

namespace mth
{

/// \addtogroup mth
/// @{

/// \brief Hard stair definition.
///
/// Additional definition for function in [xlo, xhi] segment.
/// We do linear interpolation in [xlo, xhi] segment.
///
/// \param[in] x   X value.
/// \param[in] xlo Lower bound for X.
/// \param[in] xhi Higher bound for X.
/// \param[in] ylo Value of function in (-inf, xlo].
/// \param[in] yhi Value of function in [xhi, +inf).
///
/// \return
/// Value of function in (-inf, +inf).
double
hard_stair(double x,
           double xlo,
           double xhi,
           double ylo,
           double yhi)
{
    DEBUG_CHECK_ERROR(xlo < xhi, "wrong segment for hard stair interpolation");

    if (x <= xlo)
    {
        return ylo;
    }
    else if (x >= xhi)
    {
        return yhi;
    }
    else
    {
        return ((xhi - x) * ylo + (x - xlo) * yhi) / (xhi - xlo);
    }
}

/// \brief Inner interpolation on segment.
///
/// \param[in] xlo Low x value.
/// \param[in] xhi High x value.
/// \param[in] ylo Low y value.
/// \param[in] yhi High y value.
/// \param[in] x   Argument.
///
/// \return
/// Interpolation result.
double
inner_interpolation_on_segment(double xlo,
                               double xhi,
                               double ylo,
                               double yhi,
                               double x)
{
    DEBUG_CHECK_ERROR(mth::in_bounds<double>(x, xlo, xhi),
                      "out of interval while inner interpolation");

    double idx { 1.0 / (xhi - xlo) };
    double dy { yhi - ylo };
    double dxy { ylo * xhi - yhi * xlo };

    return idx * (dy * x + dxy);
}

/// \brief Interpolation by 3 points.
///
/// Interpolation by three points.
///
/// \param[in] xlo Low value of x.
/// \param[in] xmi Middle value of x.
/// \param[in] xhi High value of x.
/// \param[in] ylo Low value of y.
/// \param[in] ymi Middle value of y.
/// \param[in] yhi High value of y.
/// \param[in] x   Argument.
///
/// \return
/// Interpolation result.
double
interpolation_by_3_points(double xlo,
                          double xmi,
                          double xhi,
                          double ylo,
                          double ymi,
                          double yhi,
                          double x)
{
    if (x <= xlo)
    {
        return ylo;
    }
    else if (x >= xhi)
    {
        return yhi;
    }
    else if (x <= xmi)
    {
        return inner_interpolation_on_segment(xlo, xmi, ylo, ymi, x);
    }
    else
    {
        return inner_interpolation_on_segment(xmi, xhi, ymi, yhi, x);
    }
}

/// \brief Linear interpolation.
///
/// \param[in] xs Arguments.
/// \param[in] ys Function values.
/// \param[in] x  Argument.
///
/// \return
/// Result value.
double
linear_interpolation(const vector<double>& xs,
                     const vector<double>& ys,
                     double x)
{
    DEBUG_CHECK_ERROR(xs.size() > 1, "not enough points for interpolation");
    DEBUG_CHECK_ERROR(xs.size() == ys.size(), "arguments count does not math fucntions values count");
    DEBUG_CHECK_ERROR(in_bounds(x, xs[0], xs.back()),
                       "interpolation value does not match interpolation interval :"
                       "  x = " + to_string(x)
                       + ", xlo = " + to_string(xs[0])
                       + ", xhi = " + to_string(xs.back()));

    size_t i = static_cast<size_t>(upper_bound(xs.begin(), xs.end(), x) - xs.begin());

    return inner_interpolation_on_segment(xs[i - 1], xs[i], ys[i - 1], ys[i], x);
}

/// @}

}
