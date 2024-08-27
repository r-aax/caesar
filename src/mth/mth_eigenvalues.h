/// \file
/// \brief Eigenvalues calculation.
///
/// Eigenvalues calculation.

#ifndef CAESAR_MTH_EIGENVALUES_H
#define CAESAR_MTH_EIGENVALUES_H

#include <vector>

using namespace std;

namespace caesar
{

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

}

#endif // !CAESAR_MTH_EIGENVALUES_H
