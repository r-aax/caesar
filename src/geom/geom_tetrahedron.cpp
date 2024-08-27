/// \file
/// \brief Tetrahedron implementation.
///
/// Tetrahedron implementation.

#include "geom_tetrahedron.h"

namespace geom
{

/// \addtogroup geom
/// @{

/// \brief Tetrahedron volume.
///
/// Tetrahedron volume.
///
/// \param[in] a First point.
/// \param[in] b Second point.
/// \param[in] c Third point.
/// \param[in] d 4th point.
///
/// \return
/// Volume.
double
tetrahedron_volume(const Vector& a,
                   const Vector& b,
                   const Vector& c,
                   const Vector& d)
{
    Vector ad, bd, cd, cr;

    Vector::sub(a, d, ad);
    Vector::sub(b, d, bd);
    Vector::sub(c, d, cd);
    Vector::cross_product(bd, cd, cr);

    return abs(ad * cr) / 6.0;
}

/// @}

}
