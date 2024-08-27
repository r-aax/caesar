/// \file
/// \brief Displaced triangle implementation.
///
/// Displaced triangle implementation.

#include "geom_displaced_triangle.h"

#include "geom_tetrahedron.h"

namespace caesar
{

namespace geom
{

/// \addtogroup geom
/// @{

/// \brief Displaced triangle volume.
///
/// Displaced triangle volume.
///
/// \param[in] a  First point.
/// \param[in] b  Second point.
/// \param[in] c  Third point.
/// \param[in] na New position of first point.
/// \param[in] nb New position of second point.
/// \param[in] nc New position of third point.
///
/// \return
/// Volume.
double
displaced_triangle_volume(const Vector& a,
                          const Vector& b,
                          const Vector& c,
                          const Vector& na,
                          const Vector& nb,
                          const Vector& nc)
{
    return tetrahedron_volume(a, b, c, nc)
           + tetrahedron_volume(a, b, nb, nc)
           + tetrahedron_volume(a, na, nb, nc);
}

/// @}

}

}
