///
/// @file
/// @brief Интерфейс класса для решения СЛАУ.
///

#ifndef MTH_SLE_H
#define MTH_SLE_H

namespace mth
{

/// @addtogroup mth
/// @{

// Решение системы двух уравнений с двумя неизвестными.
bool
solve_system_2(double a1,
               double b1,
               double c1,
               double a2,
               double b2,
               double c2,
               double *x,
               double *y);

// Решене тридиагональной системы методом прогонки.
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
