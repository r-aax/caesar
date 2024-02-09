/// \file
/// \brief Vector in 3D space.
///
/// Vector in 3D space.

#ifndef GEOM_VECTOR_H
#define GEOM_VECTOR_H

#include "utils/utils.h"

namespace geom
{

/// \addtogroup geom
/// @{

/// \brief Vector class.
class Vector
{

private:

    /// \brief X coorsinate.
    double x { 0.0 };

    /// \brief Y coordinate.
    double y { 0.0 };

    /// \brief Z coordinate.
    double z { 0.0 };

public:

    // Constructor.
    Vector();

    // Constructor from values.
    Vector(double x_,
           double y_,
           double z_);

    // Destructor.
    ~Vector();

    // Print function.
    friend ostream&
    operator<<(ostream& os,
               const Vector& v);
};

/// @}

}

#endif // GEOM_VECTOR_H
