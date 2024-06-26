///
/// @file
/// @brief Реализация класса для решения СЛАУ.
///

#include <iostream>

#include "mth_sle.h"
#include "mth_basics.h"

using namespace std;

namespace mth
{

/// @addtogroup mth
/// @{

/// @brief Решение системы двух уравнений с двумя неизвестными.
///
/// @f$ a_1 * x + b_1 * y + c_1 = 0 @f$ \n
/// @f$ a_2 * x + b_2 * y + c_2 = 0 @f$
///
/// @param [in] a1 - Коэффициент при x в первом уравнении.
/// @param [in] b1 - Коэффициент при y в первом уравнении.
/// @param [in] c1 - Свободный коэффициент в первом уравнении.
/// @param [in] a2 - Коэффициент при x во втором уравнении.
/// @param [in] b2 - Коэффициент при y во втором уравнении.
/// @param [in] c2 - Свободный коэффициент во втором уравнении.
/// @param [in] x - Указатель на первую переменную.
/// @param [in] y - Указатель на вторую переменную.
///
/// @return
/// <c>true</c>, решение найдено в штатном режиме,
/// <c>false</c>, в процессе решения произошло деление на ноль.
bool
solve_system_2(double a1,
               double b1,
               double c1,
               double a2,
               double b2,
               double c2,
               double *x,
               double *y)
{
    double d = a1 * b2 - a2 * b1;

    // При делении на ноль пусть возвращаются бесконечности.
    *x = -(c1 * b2 - c2 * b1) / d;
    *y = -(c1 * a2 - c2 * a1) / (-d);

    return !mth::is_zero(d);
}

/// @brief Решене тридиагональной системы методом прогонки.
///
/// @f$ A_i x_{i - 1} + C_i x_i + B_i x_{i + 1} = F_i, i = 1,n - 1 @f$
/// @f$ x_0 = q_0, x_n = q_n @f$
///
/// @param [in] n - Размерность системы (в системе участвуют переменные от x[0] до x[n]).
/// @param [in] q0 - Значение x0.
/// @param [in] qn - Значение qn.
/// @param [in] a - Коэффициенты матрицы под главной диагональю.
/// @param [in] c - Коэффициенты матрицы на главной диагонали.
/// @param [in] b - Коэффициенты матрицы над главной диагональю.
/// @param [in] f - Коэффициенты правой части системы.
/// @param [in] alfa - Вспомогательные коэффициенты.
/// @param [in] beta - Вспомогательные коэффициенты.
/// @param [out] x - Неизвестные.
///
/// @return
/// <c>true</c>, решение найдено в штатном режиме,
/// <c>false</c>, в процессе решения произошло деление на ноль.
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
                         double *x)
{
    // Прямой шаг.

    alfa[1] = 0.0;
    beta[1] = q0;

    for (int i = 1; i < n; i++)
    {
        double d = a[i] * alfa[i] + c[i];

        if (mth::is_zero(d))
        {
            return false;
        }

        alfa[i + 1] = -b[i] / d;
        beta[i + 1] = (f[i] - a[i] * beta[i]) / d;
    }

    // Обратный шаг.

    x[n] = qn;

    for (int i = n - 1; i >= 0; i--)
    {
        x[i] = alfa[i + 1] * x[i + 1] + beta[i + 1];
    }

    return true;
}

/// @}

}
