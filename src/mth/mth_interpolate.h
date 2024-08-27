/// \file
/// \brief Interpolation.
///
/// Work with function, interpolation, extrapolation, additional definition and etc.

#ifndef CAESAR_MTH_INTERPOLATE_H
#define CAESAR_MTH_INTERPOLATE_H

#include <utils/utils.h>

namespace caesar
{

namespace mth
{

/// \addtogroup mth
/// @{

// Hard stair function with addition definition in [xlo, xhi] segment.
double
hard_stair(double x,
           double xlo,
           double xhi,
           double ylo,
           double yhi);

// Inner interpolation on segment.
double
inner_interpolation_on_segment(double xlo,
                               double xhi,
                               double ylo,
                               double yhi,
                               double x);

// Interpolation by 3 points.
double
interpolation_by_3_points(double xlo,
                          double xmi,
                          double xhi,
                          double ylo,
                          double ymi,
                          double yhi,
                          double x);

// Linear interpolation.
double
linear_interpolation(const vector<double>& xs,
                     const vector<double>& ys,
                     double x);

/// @}

}

}

#endif // !CAESAR_MTH_INTERPOLATE_H
