/// \file
/// \brief Vector in 3D space.
///
/// Vector in 3D space.

#ifndef CAESAR_GEOM_VECTOR_H
#define CAESAR_GEOM_VECTOR_H

#include <iostream>

#include "utils/utils.h"
#include "mth/mth.h"

namespace caesar
{

namespace geom
{

/// \addtogroup geom
/// @{

/// \brief Vector class.
class Vector
{

private:

public:

    /// \brief X coordinate.
    double x { 0.0 };

    /// \brief Y coordinate.
    double y { 0.0 };

    /// \brief Z coordinate.
    double z { 0.0 };

    // Constructor.
    Vector();

    // Constructor from values.
    Vector(double x_,
           double y_,
           double z_);

    // Copy constructor.
    Vector(const Vector& v);

    // Destructor.
    ~Vector();

    // Print function.
    friend ostream&
    operator<<(ostream& os,
               const Vector& v);

    // Set.
    void
    set(double x_,
        double y_,
        double z_);

    /// \brief Set from another point.
    ///
    /// Set vector from point.
    ///
    /// \param[in] v Vector.
    inline void
    set(const Vector& v)
    {
        set(v.x, v.y, v.z);
    }

    /// \brief Set to zero.
    ///
    /// Set vector to zero.
    inline void
    zero()
    {
        set(0.0, 0.0, 0.0);
    }

    /// \brief Hash function.
    ///
    /// Hash function.
    ///
    /// \return
    /// Hash function.
    inline uint64_t
    hash() const
    {
        return utils::double_hash(x) ^ utils::double_hash(y) ^ utils::double_hash(z);
    }

    /// \brief Square of module.
    ///
    /// Square of module.
    ///
    /// \return
    /// Square of module.
    inline double
    mod2() const
    {
        return x * x + y * y + z * z;
    }

    /// \brief Module.
    ///
    /// Module.
    ///
    /// \return
    /// Module.
    inline double
    mod() const
    {
        return mth::pyth(x, y, z);
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
        return mth::pyth(x - v.x, y - v.y, z - v.z);
    }

    /// \brief Check for strict equal of two vectors.
    ///
    /// Check if two vectors are strictly equal.
    ///
    /// \param[in] v Vector.
    ///
    /// \return
    /// true - if two vectors are strictly equal,
    /// false - otherwise.
    inline bool
    is_strict_eq(const Vector& v) const
    {
        return mth::is_eq(x, v.x) && mth::is_eq(y, v.y) && mth::is_eq(z, v.z);
    }

    /// \brief Check for vectors nearest.
    ///
    /// Check if two vectors are near to each other.
    ///
    /// \param[in] v   Vector.
    /// \param[in] eps Small value.
    ///
    /// \return
    /// true - if two vectors are near,
    /// false - otherwise.
    inline bool
    is_near(const Vector& v,
            double eps = mth::Eps) const
    {
        return mth::is_near(x, v.x, eps) && mth::is_near(y, v.y, eps) && mth::is_near(z, v.z, eps);
    }

    //
    // Arithmetic.
    //

    // Addition.
    static void
    add(const Vector& a,
        const Vector& b,
        Vector& r);

    // Attition to this vector.
    void
    add(const Vector& v);

    // Subtraction.
    static void
    sub(const Vector& a,
        const Vector& b,
        Vector& r);

    // Subtraction from this vector.
    void
    sub(const Vector& v);

    // Negate vector.
    static void
    neg(const Vector& a,
        Vector& r);

    // Negate this vector.
    void
    neg();

    // Multiply by float value.
    static void
    mul(const Vector& a,
        double k,
        Vector& r);

    // Multiply this vector by float value.
    void
    mul(double k);

    // Divide by float value.
    static void
    div(const Vector& a,
        double k,
        Vector& r);

    // Divide this vector by float value.
    void
    div(double k);

    // Average value of vectors.
    static void
    avg(const Vector& a,
        const Vector& b,
        Vector& r);

    // Avegare value of three vectors.
    static void
    avg(const Vector& a,
        const Vector& b,
        const Vector &c,
        Vector& r);

    // Fused multiply add.
    static void
    fma(const Vector& a,
        double k,
        const Vector& b,
        Vector& r);

    // Fused multiple add.
    void
    fma(double k,
        const Vector& v);

    // Linear combination.
    static void
    linear_combination(const Vector& a,
                       double alpha,
                       const Vector& b,
                       double beta,
                       Vector& r);

    // Scalar product.
    friend double
    operator*(const Vector& a,
              const Vector& b);

    // Cos angle between vectors.
    static double
    angle_cos(const Vector& a,
              const Vector& b);

    // Angle between vectors.
    static double
    angle(const Vector& a,
          const Vector& b);

    // Fall angle of one vector to another.
    static double
    fall_angle(const Vector& v,
               const Vector& n);

    // Check if vectors are co-directed.
    static bool
    is_co_directed(const Vector& a,
                   const Vector& b);

    // Check if vectors are counter-directed.
    static bool
    is_counter_directed(const Vector& a,
                        const Vector& b);

    // Cross product.
    static void
    cross_product(const Vector& a,
                  const Vector& b,
                  Vector& r);

    // Triple product.
    static double
    triple_product(const Vector& a,
                   const Vector& b,
                   const Vector& c);

    // Normalize.
    void
    normalize();

    //
    // Other operations.
    //

    // Projection value on another vector.
    double
    projection_value(const Vector& base) const;

    // Calculate projection on vector.
    void
    calc_projection(const Vector& base,
                    Vector& projection) const;

    // Orthogonal decomposition.
    void
    orthogonal_decompose(const Vector& base,
                         Vector& projection,
                         Vector& orthogonal) const;


    // Outer normal to triangle.
    static void
    calc_outer_normal(const Vector& a,
                      const Vector& b,
                      const Vector& c,
                      Vector& r);

    // Calculate projection on plane.
    void
    calc_projection_on_plane(const Vector& a,
                             const Vector& b,
                             const Vector& c,
                             Vector& projection) const;

    //
    // Construct other vectors.
    //

    // Construct orth vector - direction of triangle height.
    static void
    calc_height_dir(const Vector& a,
                    const Vector& b,
                    Vector& r);

    //
    // Calculate linear characterisctics.
    //

    // Triangle min side length.
    static double
    triangle_min_side_length(const Vector& a,
                             const Vector& b,
                             const Vector& c);

    //
    // Calculate areas and volumes.
    //

    // Triangle area.
    static double
    triangle_area(const Vector& a,
                  const Vector& b,
                  const Vector& c);

    // Tetrahedron volume.
    static double
    tetrahedron_volume(const Vector& a,
                       const Vector& b,
                       const Vector& c,
                       const Vector& d);

    // Displaced triangle volume.
    static double
    displaced_triangle_volume(const Vector& ao,
                              const Vector& bo,
                              const Vector& co,
                              const Vector& an,
                              const Vector& bn,
                              const Vector& cn);
};

/// @}

}

}

#endif // !CAESAR_GEOM_VECTOR_H
