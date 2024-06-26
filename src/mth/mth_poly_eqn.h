///
/// @file
/// @brief Описание решения уравнений.
///

#ifndef MTH_POLY_EQN_H
#define MTH_POLY_EQN_H

namespace mth
{

/// @addtogroup mth
/// @{

// Поиск вещественных корней квадратного уравнения.
int
find_real_roots_eq2(double a,
                    double b,
                    double c,
                    double *roots);

// Поиск вещественных корней кубического уравнения.
int
find_real_roots_eq3(double a,
                    double b,
                    double c,
                    double d,
                    double *roots,
                    double eps_ai_bi_zero,
                    double eps_image);

// Поиск ближайшего корня.
double
nearest_root(double x,
             double *roots,
             int roots_count);

// Направленный поиск ближайшего корня.
double
directed_nearest_root(double x,
                      double *roots,
                      int roots_count,
                      double dir,
                      double max_possible_diff);

/// @}

}

#endif // !MTH_POLY_EQN_H
