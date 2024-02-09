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

    /// \brief Module.
    ///
    /// Module.
    ///
    /// \return
    /// Module.
    inline double
    mod() const
    {
        return hypot(x, y, z);
    }

    /// \brief Distance to another vector.
    ///
    /// Distance to another vector.
    ///
    /// \param[in] v Vector.
    ///
    /// \return
    /// Distance to another vector.
    inline double
    dist_to(const Vector& v) const
    {
        return hypot(x - v.x, y - v.y, z - v.z);
    }
};

/// @}

}

#endif // GEOM_VECTOR_H
