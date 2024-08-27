/// \file
/// \brief System of linear equation solving.
///
/// System of equation solving.

#ifndef MTH_SLE_H
#define MTH_SLE_H

namespace mth
{

/// \addtogroup mth
/// @{

// System of two equations with two variables.
bool
solve_system_2(double a1,
               double b1,
               double c1,
               double a2,
               double b2,
               double c2,
               double *x,
               double *y);

// Solving with tridiagonal algorithm.
bool
solve_tridiagonal_system(int n,
                         double q0,
                         double qn,
                         double *a,
                         double *c,
                         double *b,
                         double *f,
                         double *alfa,
                         double *beta,
                         double *x);

/// @}

}

#endif
