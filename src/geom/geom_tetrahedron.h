/// \file
/// \brief Tetrahedron declaration.
///
/// Tetrahedron declaration.

#ifndef GEOM_TETRAHEDRON_H
#define GEOM_TETRAHEDRON_H

#include "geom_vector.h"

namespace geom
{

/// \addtogroup geom
/// @{

// Tetrahedron volume.
double
tetrahedron_volume(const Vector& a,
                   const Vector& b,
                   const Vector& c,
                   const Vector& d);

/// @}

}

#endif // !GEOM_TETRAHEDRON_H
