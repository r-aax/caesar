/// \file
/// \brief Polynom equations.
///
/// Polynom equations.

#ifndef CAESAR_MTH_POLY_EQN_H
#define CAESAR_MTH_POLY_EQN_H

namespace caesar
{

namespace mth
{

/// \addtogroup mth
/// @{

// Find real roots of square equation.
int
find_real_roots_eq2(double a,
                    double b,
                    double c,
                    double *roots);

// Find real roots of cubic equation.
int
find_real_roots_eq3(double a,
                    double b,
                    double c,
                    double d,
                    double *roots,
                    double eps_ai_bi_zero,
                    double eps_image);

// Find nearest root.
double
nearest_root(double x,
             double *roots,
             int roots_count);

// Directed look for nearest root.
double
directed_nearest_root(double x,
                      double *roots,
                      int roots_count,
                      double dir,
                      double max_possible_diff);

/// @}

}

}

#endif // !CAESAR_MTH_POLY_EQN_H
