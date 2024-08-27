/// \file
/// \brief Polynom equations.
///
/// Polynom equations implementation.

#include "mth_poly_eqn.h"

#include <iostream>
#include <complex>
#include <limits>

#include "mth_basics.h"

using namespace std;

namespace mth
{

/// \addtogroup mth
/// @{

/// \brief Find square equation real roots.
///
/// @f$ a x^2 + b x + c = 0 @f$
///
/// \param[in]  a     Coefficient for при x^2.
/// \param[in]  b     Coefficient for x.
/// \param[in]  c     Free coefficient.
/// \param[out] roots Pointer to result roots.
///
/// \return
/// Count of roots (from 0 to 2).
/// It is possible to appear equal roots.
int
find_real_roots_eq2(double a,
                    double b,
                    double c,
                    double *roots)
{
    if (mth::is_zero(a))
    {
        // Degenerative case.
        // Ignore it.
        return 0;
    }

    double d = b * b - 4.0 * a * c;

    if (d < 0.0)
    {
        return 0;
    }

    double sd = sqrt(d);

    roots[0] = (-b + sd) / (2.0 * a);
    roots[1] = (-b - sd) / (2.0 * a);

    return 2;
}

/// \brief Find real root for cubic equation.
///
/// @f$ a x^3 + b x^2 + c x + d = 0 @f$
///
/// \param[in]  a              Coefficient for x^3.
/// \param[in]  b              Coefficient for x^2.
/// \param[in]  c              Coefficient for x.
/// \param[in]  d              Free coefficient.
/// \param[out] roots          Pointer to results.
/// \param[in]  eps_ai_bi_zero Small value for alfa and beta check.
/// \param[in]  eps_image      Small value for decline image parts
///
/// \return
/// Count of real roots (from 0 to 3).
/// It is possible to appear equal roots.
int
find_real_roots_eq3(double a,
                    double b,
                    double c,
                    double d,
                    double *roots,
                    double eps_ai_bi_zero,
                    double eps_image)
{
    if (mth::is_zero(a))
    {
        return find_real_roots_eq2(b, c, d, roots);
    }

    double p = (3.0 * a * c - b * b) / (3.0 * a * a);
    double q = (2.0 * b * b * b - 9.0 * a * b * c + 27.0 * a * a * d) / (27.0 * a * a * a);

    complex<double> Q(p * p * p / 27.0 + q * q / 4.0, 0.0);
    complex<double> sQ = sqrt(Q);
    complex<double> alfas[3], betas[3];
    complex<double> s(0.0, sqrt(3.0));
    complex<double> pl;

    // Alfas and betas generation.
    pl = -q / 2.0 + sQ;
    alfas[0] = pow(pl, 1.0 / 3.0);
    alfas[1] = alfas[0] * (-1.0 + s) / 2.0;
    alfas[2] = alfas[0] * (-1.0 - s) / 2.0;
    pl = -q / 2.0 - sQ;
    betas[0] = pow(pl, 1.0 / 3.0);
    betas[1] = betas[0] * (-1.0 + s) / 2.0;
    betas[2] = betas[0] * (-1.0 - s) / 2.0;

    // Alfas and betas pairing.
    int root_i = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            complex<double> ch = alfas[i] * betas[j] + p / 3.0;

            if (abs(ch) < eps_ai_bi_zero)
            {
                complex<double> x = alfas[i] + betas[j] - b / (3.0 * a);

                if (abs(imag(x)) < eps_image)
                {
                    roots[root_i] = real(x);
                    root_i++;
                }

                break;
            }
        }
    }

    return root_i;
}

/// \brief Nearest root searching.
///
/// \param[in] x           Old root.
/// \param[in] roots       New roots.
/// \param[in] roots_count New roots count.
///
/// \return
/// New root value.
double
nearest_root(double x,
             double *roots,
             int roots_count)
{
    double cur_r = x;
    double cur_diff = numeric_limits<double>::max();

    for (int i = 0; i < roots_count; i++)
    {
        double r = roots[i];
        double diff = abs(r - x);

        if (diff < cur_diff)
        {
            cur_r = r;
            cur_diff = diff;
        }
    }

    return cur_r;
}

/// \brief Nearest root directed search.
///
/// First we find nearest root.
/// Then direction is taken into account:
/// dir > 0 - try to find root greater that current,
/// dir < 0 - try to find root less than current,
/// dir == 0 - return as is
///
/// \param[in] x                 Old root.
/// \param[in] roots             New roots.
/// \param[in] roots_count       New roots count.
/// \param[in] dir               Search direction.
/// \param[in] max_possible_diff Maximum diff to nearest root with given direction.
///
/// \return
/// New root value.
double
directed_nearest_root(double x,
                      double *roots,
                      int roots_count,
                      double dir,
                      double max_possible_diff)
{
    double cur_r = nearest_root(x, roots, roots_count);
    double cur_diff = numeric_limits<double>::max();

    if (dir > 0.0)
    {
        for (int i = 0; i < roots_count; i++)
        {
            double r = roots[i];

            if (r > x)
            {
                double diff = abs(r - x);

                if ((diff < cur_diff) && (diff < max_possible_diff))
                {
                    cur_r = r;
                    cur_diff = diff;
                }
            }
        }
    }
    else if (dir < 0.0)
    {
        for (int i = 0; i < roots_count; i++)
        {
            double r = roots[i];

            if (r < x)
            {
                double diff = abs(r - x);

                if ((diff < cur_diff) && (diff < max_possible_diff))
                {
                    cur_r = r;
                    cur_diff = diff;
                }
            }
        }
    }

    return cur_r;
}

/// @}

}
