/// \file
/// \brief Prismatoid functions.
///
/// Prismatoid functions.

#ifndef GEOM_PRISMATOID_H
#define GEOM_PRISMATOID_H

#include "geom_vector.h"

namespace geom
{

/// \addtogroup geom
/// @{

// Define coefficients for prismatoid volume.
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
                               double& c);

/// @}

}

#endif // !GEOM_PRISMATOID_H
