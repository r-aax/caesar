/// \file
/// \brief Linear algebra functions.
///
/// Linear algebra functions.

#include "mth_linear_algebra.h"

#include <iostream>

#include "mth_poly_eqn.h"
#include "mth_basics.h"
#include "utils/utils.h"

using namespace std;

namespace caesar
{

namespace mth
{

/// \addtogroup mth
/// @{

/// \brief Transpose.
///
/// Transpose matrix.
///
/// \param[in]  m Matrix,
/// \param[out] t Transposed matrix.
void
transpose(const vector<vector<double>>& m,
          vector<vector<double>>& t)
{
    DEBUG_CHECK_ERROR(t.size() == 0, "result is generated during transpose");

    size_t r { m.size() }, c { m[0].size() };

    // init rows of out matrix
    for (size_t j = 0; j < c; ++j)
    {
        t.push_back(vector<double>());
    }

    for (size_t i = 0; i < r; ++i)
    {
        for (size_t j = 0; j < c; ++j)
        {
            t[j].push_back(m[i][j]);
        }
    }
}

/// \brief Dot matrix on vector.
///
/// Dot matrix on vector.
///
/// \param[in]  m Matrix.
/// \param[in]  v Vector.
/// \param[out] d Result.
void
dot(const vector<vector<double>>& m,
    const vector<double>& v,
    vector<double>& d)
{
    DEBUG_CHECK_ERROR(d.size() == 0, "result is generated during dot");

    size_t mr { m.size() }, mc { m[0].size() };

    DEBUG_CHECK_ERROR(mc == v.size(), "wrong matrices sizes for dot");

    // Init result.
    for (size_t i = 0; i < mr; ++i)
    {
        d.push_back(0.0);
    }

    // Perform dot.
    for (size_t i = 0; i < mr; ++i)
    {
        for (size_t j = 0; j < mc; ++j)
        {
            d[i] += (m[i][j] * v[j]);
        }
    }
}

/// \brief Dot matrices.
///
/// Matrices multiplication.
///
/// \param[in]  a First matrix.
/// \param[in]  b Second matrix.
/// \param[out] d Dot.
void
dot(const vector<vector<double>>& a,
    const vector<vector<double>>& b,
    vector<vector<double>>& d)
{
    DEBUG_CHECK_ERROR(d.size() == 0, "result is generated during dot");

    size_t ar { a.size() }, ac { a[0].size() }, bc { b[0].size() };

    DEBUG_CHECK_ERROR(ac == b.size(), "wrong matrices sizes for dot");

    // Init result matrix size.
    for (size_t i = 0; i < ar; ++i)
    {
        d.push_back(vector<double>(bc, 0.0));
    }

    // Perform dot.
    for (size_t i = 0; i < ar; ++i)
    {
        for (size_t j = 0; j < bc; ++j)
        {
            for (size_t k = 0; k < ac; ++k)
            {
                d[i][j] += (a[i][k] * b[k][j]);
            }
        }
    }
}

/// \brief Promote matrix leader for pos-th position.
///
/// Promote matrix leader line.
///
/// \param[in,out] m   Matrix.
/// \param[in]     pos POsition.
void
promote_leader(vector<vector<double>>& m,
               size_t pos)
{
    size_t n { m.size() };

    if (pos >= n - 1)
    {
        // Nothing to promote.
        return;
    }

    size_t max_pos { pos };
    double max_val { abs(m[pos][pos]) };

    for (size_t i = pos + 1; i < n; ++i)
    {
        double cur_val { abs(m[i][pos]) };

        if (cur_val > max_val)
        {
            max_pos = i;
            max_val = cur_val;
        }
    }

    if (max_pos != pos)
    {
        swap(m[pos], m[max_pos]);
    }
}

/// \brief Mul and add line.
///
/// Mul and add line.
///
/// \param[in,out] m Matrix.
/// \param[in]     i Source line.
/// \param[in]     f Factor.
/// \param[in]     j Destination line.
void
mul_and_add_line(vector<vector<double>>& m,
                 size_t i,
                 double f,
                 size_t j)
{
    size_t n { m[0].size() };

    for (size_t k = 0; k < n; ++k)
    {
        m[j][k] += (m[i][k] * f);
    }
}

/// \brief Determinant for 3x3 matrix.
///
/// Determinant for 3x3 matrix.
///
/// \param[in] m Matrix.
///
/// \return
/// Determinant.
double
det_3x3(const vector<vector<double>>& m)
{
    double a { m[0][0] }, b { m[0][1] }, c { m[0][2] },
           d { m[1][0] }, e { m[1][1] }, f { m[1][2] },
           g { m[2][0] }, h { m[2][1] }, i { m[2][2] };

    return (a * e * i) + (b * f * g) + (c * d * h)
           - (c * e * g) - (b * d * i) - (a * f * h);
}

/// \brief Find real eigenvalues for matrix 3x3.
///
/// Find eigenvalues for matrix 3x3.
///
/// \param[in]  m   Matrix.
/// \param[out] eig Eigenvalues.
void
find_matrix_3x3_real_eigenvalues(const vector<vector<double>>& m,
                                 vector<double>& eig)
{
    //     | (a - x)    b       c    |
    // det |    d    (e - x)    f    | = 0
    //     |    g       h    (i - x) |

    double a { m[0][0] }, b { m[0][1] }, c { m[0][2] },
           d { m[1][0] }, e { m[1][1] }, f { m[1][2] },
           g { m[2][0] }, h { m[2][1] }, i { m[2][2] };

    // det = (a - x)(e - x)(i - x) + cdh + bfg
    //       - (e - x)cg - (a - x)fh - (i - x)bd

    // coefficients for cubic equation
    double A { -1.0 };
    double B { a + e + i };
    double C { -(a * e) - (a * i) - (e * i) + (c * g) + (f * h) + (b * d) };
    double D { (a * e * i) + (c * d * h) + (b * f * g) - (e * c * g) - (a * f * h) - (i * b * d) };

    // roots
    double roots[3];

    // solve cubic equation
    int roots_count { find_real_roots_eq3(A, B, C, D, &roots[0], 1.0e-15, 1.0e-15) };

    // fill eigenvalues with roots
    for (int ii = 0; ii < roots_count; ++ii)
    {
        eig.push_back(roots[ii]);
    }

    // sort roots - big values first
    sort(eig.begin(), eig.end(), [] (double v1, double v2) { return v1 > v2; });
}

/// @}

}

}
