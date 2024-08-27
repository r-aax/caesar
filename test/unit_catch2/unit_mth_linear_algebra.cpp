/// \file
/// \brief Tests for linear algebra.
///
/// Tests for linear algebra.

#include <catch2/catch_test_macros.hpp>
#include "caesar.h"

using namespace caesar;

TEST_CASE("Eigenvalues and eigenvectors", "[mth]")
{
    SECTION("eigenvalues for 3x3 matrix")
    {
        vector<vector<double>> m(3, vector<double>(3, 1.0));
        vector<double> eig;

        mth::find_matrix_3x3_real_eigenvalues(m, eig);

        CHECK(eig.size() == 3);
        CHECK(mth::is_near(eig[0], 3.0));
        CHECK(mth::is_near(eig[1], 0.0));
        CHECK(mth::is_near(eig[2], 0.0));
    }

    SECTION("eigenvalues for 3x3 matrix")
    {
        vector<vector<double>> m(3, vector<double>(3, 1.0));
        vector<double> eig;

        m[0][0] = 2.0;
        m[1][1] = 2.0;
        m[2][2] = 2.0;

        mth::find_matrix_3x3_real_eigenvalues(m, eig);

        CHECK(eig.size() == 3);
        CHECK(mth::is_near(eig[0], 4.0));
        CHECK(mth::is_near(eig[1], 1.0));
        CHECK(mth::is_near(eig[2], 1.0));
    }

    SECTION("eigenvalues for 3x3 matrix")
    {
        vector<vector<double>> m
        {
            vector<double> { 0.0, 1.0, 0.0 },
            vector<double> { 1.0, 5.0, 1.0 },
            vector<double> { 0.0, 1.0, 2.0 }
        };
        vector<double> eig;

        mth::find_matrix_3x3_real_eigenvalues(m, eig);

        CHECK(eig.size() == 3);
        CHECK(mth::is_near(eig[0], 5.471, 0.01));
        CHECK(mth::is_near(eig[1], 1.739, 0.01));
        CHECK(mth::is_near(eig[2], -0.21, 0.01));
    }
}
