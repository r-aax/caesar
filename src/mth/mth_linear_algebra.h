/// \file
/// \brief Linear algebra functions.
///
/// Some linear algebra functions.

#ifndef MTH_LINEAR_ALGEBRA_H
#define MTH_LINEAR_ALGEBRA_H

#include <vector>

using namespace std;

namespace mth
{

/// \addtogroup mth
/// @{

// Transpose.
void
transpose(const vector<vector<double>>& m,
          vector<vector<double>>& t);

// Dot matrix on vector.
void
dot(const vector<vector<double>>& m,
    const vector<double>& v,
    vector<double>& d);

// Dot matrices.
void
dot(const vector<vector<double>>& a,
    const vector<vector<double>>& b,
    vector<vector<double>>& d);

// Promote matrix leader for pos-th position.
void
promote_leader(vector<vector<double>>& m,
               size_t pos);

// Mul and add line.
void
mul_and_add_line(vector<vector<double>>& m,
                 size_t i,
                 double f,
                 size_t j);

// Determinant for 3x3 matrix.
double
det_3x3(const vector<vector<double>>& m);

// Find real eigenvalues.
void
find_matrix_3x3_real_eigenvalues(const vector<vector<double>>& m,
                                 vector<double>& eig);

/// @}

}

#endif // !MTH_LINEAR_ALGEBRA_H
