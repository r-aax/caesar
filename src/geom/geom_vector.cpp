/// \file
/// \brief Vector realization.
///
/// Realization of Vector in 3D space.

#include "geom_vector.h"

namespace geom
{

/// \addtogroup geom
/// @{

/// \brief Default constructor.
Vector::Vector()
{
}

/// \brief Constructor from values.
///
/// Constructor from 3 values.
///
/// \param[in] x X coordinate.
/// \param[in] y Y coordinate.
/// \param[in] z Z coordinate.
Vector::Vector(double x_,
               double y_,
               double z_)
    : x { x_ },
      y { y_ },
      z { z_ }
{
}

/// \brief Defatult destructor.
Vector::~Vector()
{
}

/// \brief Print function.
///
/// Print vector to stream.
///
/// \param[in] os Output stream.
/// \param[in] v Vector.
ostream&
operator<<(ostream& os,
           const Vector& v)
{
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";

    return os;
}


/// @}

}
