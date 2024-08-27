/// \file
/// \brief Displaced triangle declaration.
///
/// Displaced triangle declaration.

#ifndef CAESAR_GEOM_DISPLACED_TRIANGLE_H
#define CAESAR_GEOM_DISPLACED_TRIANGLE_H

#include "geom_vector.h"

namespace caesar
{

namespace geom
{

/// \addtogroup geom
/// @{

// Displaced triangle volume.
double
displaced_triangle_volume(const Vector& a,
                          const Vector& b,
                          const Vector& c,
                          const Vector& na,
                          const Vector& nb,
                          const Vector& nc);

/// @}

}

}

#endif // !CAESAR_GEOM_DISPLACED_TRIANGLE_H
