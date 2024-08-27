/// \file
/// \brief System of linear equations solving.
///
/// System of linear equations solving.

#include "mth_sle.h"

#include <iostream>

#include "mth_basics.h"

using namespace std;

namespace caesar
{

namespace mth
{

/// \addtogroup mth
/// @{

/// \brief Two equations with two variables.
///
/// @f$ a_1 * x + b_1 * y + c_1 = 0 @f$ \n
/// @f$ a_2 * x + b_2 * y + c_2 = 0 @f$
///
/// \param[in] a1 Coefficient for x in the first equation.
/// \param[in] b1 Coefficient for y in the first equation.
/// \param[in] c1 Free coefficient in the first equation.
/// \param[in] a2 Coefficient for x in the second equation.
/// \param[in] b2 Coefficient for y in the second equation.
/// \param[in] c2 Free coefficient in the second equation.
/// \param[in] x  First variable pointer.
/// \param[in] y  Second variable pointer.
///
/// \return
/// true - if system is solved,
/// false - otherwise.
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

    // Let be infinities if d is zero.
    *x = -(c1 * b2 - c2 * b1) / d;
    *y = -(c1 * a2 - c2 * a1) / (-d);

    return !mth::is_zero(d);
}

/// \brief Tridiagonal system solving.
///
/// @f$ A_i x_{i - 1} + C_i x_i + B_i x_{i + 1} = F_i, i = 1,n - 1 @f$
/// @f$ x_0 = q_0, x_n = q_n @f$
///
/// \param[in]  n    System dimension (we use variables x[0] .. x[n]).
/// \param[in]  q0   Value q0.
/// \param[in]  qn   Value qn.
/// \param[in]  a    Coefficients under main diagonal.
/// \param[in]  c    Coefficients on main diagonal.
/// \param[in]  b    Coefficients above main diagonal.
/// \param[in]  f    Coefficients in the right part.
/// \param[in]  alfa Help coefficients.
/// \param[in]  beta Help coefficients.
/// \param[out] x    Variables.
///
/// \return
/// true - if system is solved with common result,
/// false - if we encountered division by zero.
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
    // Forward step.

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

    // Back step.

    x[n] = qn;

    for (int i = n - 1; i >= 0; i--)
    {
        x[i] = alfa[i + 1] * x[i + 1] + beta[i + 1];
    }

    return true;
}

/// @}

}

}
