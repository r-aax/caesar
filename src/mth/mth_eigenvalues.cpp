/// \file
/// \brief Eigenvalues implementation.
///
/// Eigenvalues implementation.

#include "mth_eigenvalues.h"

#include <iostream>

#ifndef COMPILE_DISABLE_EIGEN
// Use extern library for eigenvalues only here.
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Eigenvalues>
#endif // !COMPILE_DISABLE_EIGEN

#include "utils/utils.h"

namespace caesar
{

namespace mth
{

/// \addtogroup mth
/// @{

/// \brief Calculate eigenvalues and eigenvectors for matrix.
///
/// Calculate eigenvalues and eigenvectors.
///
/// \param[in]  m       Matrix.
/// \param[out] values  Eigenvalues.
/// \param[out] vectors Eigenvectors.
void
calc_eigenvalues_and_eigenvectors(const vector<vector<double>>& m,
                                  vector<double>& values,
                                  vector<vector<double>>& vectors)
{

#ifdef COMPILE_DISABLE_EIGEN

    (void)m;
    (void)values;
    (void)vectors;

    NOT_IMPLEMENTED;

#else // !COMPILE_DISABLE_EIGEN

    // We use this function only for calculating 3x3 matrices.
    DEBUG_CHECK_ERROR((m.size() == 3) && (m[0].size() == 3), "we work only with 3x3 matrix");

    // Define matrix.
    Eigen::MatrixXd a(3, 3);

    // Init matrix.
    for (size_t i = 0; i < 3; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            a(static_cast<Eigen::Index>(i),
              static_cast<Eigen::Index>(j)) = m[i][j];
        }
    }

    // Define vectors for eigenvalues and eigenvectors
    Eigen::MatrixXd vals;
    Eigen::MatrixXd vecs;

    // Object for calculating eigenvalues and eigenvectors.
    Eigen::EigenSolver<Eigen::MatrixXd> sol(a);

    // Calculate eigenvalues and eigenvectors.
    // NB!
    // For out purposes all our eigenvalues are real.
    vals = sol.eigenvalues().real();
    vecs = sol.eigenvectors().real();

    // Copy back eigenvalues.
    for (size_t i = 0; i < 3; ++i)
    {
        values[i] = vals(static_cast<Eigen::Index>(i));
    }

    // Copyback eigenvectors.
    for (size_t i = 0; i < 3; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            // Invert indices.
            vectors[i][j] = vecs(static_cast<Eigen::Index>(j),
                                 static_cast<Eigen::Index>(i));
        }
    }

    // We should return sorted array of eigenvalues.
    // Eigenvectors must correspond to eigenvalues.
    // Since there is only 3 eigenvalues, sort it manally.

#define SWAP(I, J) \
    if (values[(I)] > values[(J)]) \
    { \
        swap(values[(I)], values[(J)]); \
        swap(vectors[(I)], vectors[(J)]); \
    }

    SWAP(2, 1)
    SWAP(1, 0)
    SWAP(2, 1)

#undef SWAP

#endif // COMPILE_DISABLE_EIGEN

}

/// @}

}

}
