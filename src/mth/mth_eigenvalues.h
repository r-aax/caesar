/// \file
/// \brief Eigenvalues calculation.
///
/// Eigenvalues calculation.

#ifndef MTH_EIGENVALUES_H
#define MTH_EIGENVALUES_H

#include <vector>

using namespace std;

namespace mth
{

/// \addtogroup mth
/// @{

// Calculate eigenvalues and eigenvectors for matrix.
void
calc_eigenvalues_and_eigenvectors(const vector<vector<double>>& m,
                                  vector<double>& values,
                                  vector<vector<double>>& vectors);

/// @}

}

#endif // !MTH_EIGENVALUES_H
