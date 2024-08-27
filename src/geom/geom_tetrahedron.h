/// \file
/// \brief Tetrahedron declaration.
///
/// Tetrahedron declaration.

#ifndef CAESAR_GEOM_TETRAHEDRON_H
#define CAESAR_GEOM_TETRAHEDRON_H

#include "geom_vector.h"

namespace caesar
{

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

}

#endif // !CAESAR_GEOM_TETRAHEDRON_H
