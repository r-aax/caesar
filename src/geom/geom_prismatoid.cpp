/// \file
/// \brief Prismatoid functions implementation.
///
/// Prismatoid functions implementation.

#include "geom_prismatoid.h"

namespace caesar
{

namespace geom
{

/// \addtogroup geom
/// @{

/// \brief Define coefficients for prismatoid volume.
///
/// Coefficients of prismatoid volume.
///
/// source:
/// Tong X., Thompson D., Arnoldus Q., Collins E., Luke E.
/// Three-dimensional surface evolution and mesh deformation for aircraft icing applications.
/// formulas (6, 7)
///
/// \param[in]  v1 Vector of base point.
/// \param[in]  v2 Vector of base point.
/// \param[in]  v3 Vector of base point.
/// \param[in]  n1 Direction from base point.
/// \param[in]  n2 Direction from base point.
/// \param[in]  n3 Direction from base point.
/// \param[in]  n  Normal of base.
/// \param[out] a  First coefficient.
/// \param[out] b  Second coefficient.
/// \param[out] c  Third coefficient.
void
prismatoid_volume_coefficients(const Vector& v1,
                               const Vector& v2,
                               const Vector& v3,
                               const Vector& n1,
                               const Vector& n2,
                               const Vector& n3,
                               const Vector& n,
                               double& a,
                               double& b,
                               double& c)
{
    Vector v21, v31, u1, u2, u3, u21, u31;
    Vector v21_v31, v21_u31, u21_v31, u21_u31, tmp;

    // p_ij, u_ij
    Vector::sub(v2, v1, v21);
    Vector::sub(v3, v1, v31);
    Vector::div(n1, (n * n1), u1);
    Vector::div(n2, (n * n2), u2);
    Vector::div(n3, (n * n3), u3);
    Vector::sub(u2, u1, u21);
    Vector::sub(u3, u1, u31);

    // Coefficients calculation.
    Vector::cross_product(v21, v31, v21_v31);
    Vector::cross_product(v21, u31, v21_u31);
    Vector::cross_product(u21, v31, u21_v31);
    Vector::add(v21_u31, u21_v31, tmp);
    Vector::cross_product(u21, u31, u21_u31);
    a = 0.5 * v21_v31.mod();
    b = 0.25 * (tmp * n);
    c = (1.0 / 6.0) * (u21_u31 * n);
}

/// @}

}

}
