/// \file
/// \brief Vector realization.
///
/// Realization of Vector in 3D space.

#include "geom_vector.h"
#include "utils/utils.h"

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
/// \param[in] x_ X coordinate.
/// \param[in] y_ Y coordinate.
/// \param[in] z_ Z coordinate.
Vector::Vector(double x_,
               double y_,
               double z_)
    : x { x_ },
      y { y_ },
      z { z_ }
{
}

/// \brief Copy constructor.
///
/// Copy constructor.
///
/// \param[in] v Vector.
Vector::Vector(const Vector& v)
    : x { v.x },
      y { v.y },
      z { v.z }
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
/// \param[in] v  Vector.
ostream&
operator<<(ostream& os,
           const Vector& v)
{
    os << "{" << v.x << ", " << v.y << ", " << v.z << "}";

    return os;
}

/// \brief Set.
///
/// Set components of vector.
///
/// \param[in] x_ Component X.
/// \param[in] y_ Component Y.
/// \param[in] z_ Component Z.
void
Vector::set(double x_,
            double y_,
            double z_)
{
    x = x_;
    y = y_;
    z = z_;
}

//
// Arithmetic.
//

/// \brief Addition.
///
/// Addition.
///
/// \param[in]  a First vector.
/// \param[in]  b Second vector.
/// \param[out] r Result.
void
Vector::add(const Vector& a,
            const Vector& b,
            Vector& r)
{
    r.x = a.x + b.x;
    r.y = a.y + b.y;
    r.z = a.z + b.z;
}

/// \brief Attition to this vector.
///
/// Addition to this vector.
///
/// \param[in] v Vector to add.
void
Vector::add(const Vector& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
}

/// \brief Subtraction.
///
/// Subtraction.
///
/// \param[in]  a First vector.
/// \param[in]  b Seconds vector.
/// \param[out] r Result.
void
Vector::sub(const Vector& a,
            const Vector& b,
            Vector& r)
{
    r.x = a.x - b.x;
    r.y = a.y - b.y;
    r.z = a.z - b.z;
}

/// \brief Subtraction from this vector.
///
/// Subtraction from this vector.
///
/// \param[in] v Vector to subtract.
void
Vector::sub(const Vector& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
}

/// \brief Negate vector.
///
/// Negate.
///
/// \param[in]  a Vector.
/// \param[out] r Result.
void
Vector::neg(const Vector& a,
            Vector& r)
{
    r.x = -a.x;
    r.y = -a.y;
    r.z = -a.z;
}

/// \brief Negate this vector.
///
/// Negate this vector.
void
Vector::neg()
{
    x = -x;
    y = -y;
    z = -z;
}

/// \brief Multiply by float value.
///
/// Multiply by float value.
///
/// \param[in]  a Vector.
/// \param[in]  k Coefficient.
/// \param[out] r Result.
void
Vector::mul(const Vector& a,
            double k,
            Vector& r)
{
    r.x = a.x * k;
    r.y = a.y * k;
    r.z = a.z * k;
}

/// \brief Multiply this vector by float value.
///
/// Multiply this vector by float value.
///
/// \param[in] k Coefficient.
void
Vector::mul(double k)
{
    x *= k;
    y *= k;
    z *= k;
}

/// \brief Divide by float value.
///
/// Divide by float value.
///
/// \param[in]  a Vector.
/// \param[in]  k Coefficient.
/// \param[out] r Result.
void
Vector::div(const Vector& a,
            double k,
            Vector& r)
{
    DEBUG_CHECK_ERROR(!mth::is_zero(k), "vector division by zero");

    mul(a, 1.0 / k, r);
}

/// \brief Divide this vector by float value.
///
/// Divide this vector by float value.
///
/// \param[in] k Coefficient.
void
Vector::div(double k)
{
    DEBUG_CHECK_ERROR(!mth::is_zero(k), "vector division by zero");

    mul(1.0 / k);
}

/// \brief Average value of vector.
///
/// Average value of two vectors.
///
/// \param[in]  a First vector.
/// \param[in]  b Second vector.
/// \param[out] r Result.
void
Vector::avg(const Vector& a,
            const Vector& b,
            Vector& r)
{
    add(a, b, r);
    r.mul(0.5);
}

/// \brief Avegare value of three vectors.
///
/// Average value of three vectors.
///
/// \param[in]  a First vector.
/// \param[in]  b Second vector.
/// \param[in]  c Third vector.
/// \param[out] r Result.
void
Vector::avg(const Vector& a,
            const Vector& b,
            const Vector &c,
            Vector& r)
{
    add(a, b, r);
    add(r, c, r);
    r.mul(1.0 / 3.0);
}

/// \brief Fused multiply add.
///
/// Fused multiply-add.
///
/// \param[in]  a First vector.
/// \param[in]  k Coefficient.
/// \param[in]  b Second vector.
/// \param[out] r Result.
void
Vector::fma(const Vector& a,
            double k,
            const Vector& b,
            Vector& r)
{
    r.x = a.x * k + b.x;
    r.y = a.y * k + b.y;
    r.z = a.z * k + b.z;
}

/// \brief Fused multiple add.
///
/// Fused multiply-add and write result to this vector.
///
/// \param[in] k Coefficient.
/// \param[in] v Vector.
void
Vector::fma(double k,
            const Vector& v)
{
    x = x * k + v.x;
    y = y * k + v.y;
    z = z * k + v.z;
}

/// \brief Linear combination.
///
/// Linear combination:
///
/// @f$ \vec{r} = \alpha \vec{a} + \beta \vec{b} @f$
///
/// \param[in]  a     First vector.
/// \param[in]  alpha First vector weight.
/// \param[in]  b     Second vector.
/// \param[in]  beta  Second vector weight.
/// \param[out] r     Result.
void
Vector::linear_combination(const Vector& a,
                           double alpha,
                           const Vector& b,
                           double beta,
                           Vector& r)
{
    mul(a, alpha, r);
    fma(b, beta, r, r);
}

/// \brief Scalar product.
///
/// Scalar product.
///
/// \param[in]  a First vector.
/// \param[in]  b Second vector.
///
/// \return
/// Scalar product.
double
operator*(const Vector& a,
          const Vector& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

/// \brief Cos angle between vector.
///
/// Cosine of angle between vectors.
/// 
/// @f$ \vec{a} \cdot \vec{b} = |\vec{a}| \cdot |\vec{b}| \cdot \cos \alpha @f$
/// @f$ \cos \alpha = \frac{\vec{a} \cdot \vec{b}}{|\vec{a}| \cdot |\vec{b}|} @f$
///
/// \param[in] a First vector.
/// \param[in] b Second vector.
///
/// \return
/// Cosine of angle.
double
Vector::angle_cos(const Vector& a,
                  const Vector& b)
{
    return (a * b) / (a.mod() * b.mod());
}

/// \brief Angle between vectors (rad).
///
/// Angle between two vectors (from 0.0 to pi).
///
/// \param[in] a First vector.
/// \param[in] b Second vector.
///
/// \return
/// Angle (rad).
double
Vector::angle(const Vector& a,
              const Vector& b)
{
    return acos(angle_cos(a, b));
}

/// \brief Fall angle of one vector to another (rad).
///
///               | angle = pi
///               | fall_angle = 0
///               V
///                 <----- angle = pi/2
///                        fall_angle = pi/2
///               ^
///               | n
///               |
///     ----------*----------
///
/// \param[in] v Vector.
/// \param[in] n Target vector.
///
/// \return
/// Fall angle (rad).
double
Vector::fall_angle(const Vector& v,
                   const Vector& n)
{
    double a = angle(v, n);

    if (a <= 0.5 * mth::Pi)
    {
        // Orthogonal.
        // Falling has no effect.
        return 0.5 * mth::Pi;
    }
    else
    {
        return mth::Pi - a;
    }
}

/// \brief Check if vectors are co-directed.
///
/// Check if vectors are co-directed.
///
/// \param[in] a First vector.
/// \param[in] b Second vector.
///
/// \return
/// true - if vectors are co-directed,
/// false - otherwise.
bool
Vector::is_co_directed(const Vector& a,
                       const Vector& b)
{
    double ca = angle_cos(a, b);

    return mth::is_near(ca, 1.0);
}

/// \brief Check if vectors are counter-directed.
///
/// Check if vectors are counter-directed.
///
/// \param[in] a First vector.
/// \param[in] b Second vector.
///
/// \return
/// true - if vectors are counter-directed,
/// false - otherwise.
bool
Vector::is_counter_directed(const Vector& a,
                            const Vector& b)
{
    double ca = angle_cos(a, b);

    return mth::is_near(ca, -1.0);
}

/// \brief Cross product.
///
/// Subtraction.
///
/// \param[in]  a First vector.
/// \param[in]  b Seconds vector.
/// \param[out] r Result.
void
Vector::cross_product(const Vector& a,
                      const Vector& b,
                      Vector& r)
{
    r.x = a.y * b.z - a.z * b.y;
    r.y = a.z * b.x - a.x * b.z;
    r.z = a.x * b.y - a.y * b.x;
}

/// \brief Triple product.
///
/// Triple product.
///
/// \param[in] a First vector.
/// \param[in] b Seconds vector.
/// \param[in] c Third vector.
///
/// \return
/// Result of triple product.
double
Vector::triple_product(const Vector& a,
                       const Vector& b,
                       const Vector& c)
{
    Vector t;

    cross_product(b, c, t);

    return a * t;
}

/// \brief Normalize.
///
/// Normalize vector.
void
Vector::normalize()
{
    double m = mod();

    if (!mth::is_zero(m))
    {
        div(m);
    }
}

//
// Other operations.
//

/// \brief Projection value on another vector.
///
/// Calculate projection value on another vector.
///
/// @f$ \vec{v} \cdot \vec{base} = |\vec{v}| \cdot |\vec{base}| \cdot \cos \alpha = p \cdot |\vec{base}| @f$
/// @f$ p = \frac{\vec{v} \cdot \vec{base}}{|\vec{base}|} @f$
///
/// \param[in] base Base vector.
///
/// \return
/// Projection value.
double
Vector::projection_value(const Vector& base) const
{
    return (*this * base) / base.mod();
}

/// \brief Calculate projection on vector.
///
/// \param[in]  base       Base vector.
/// \param[out] projection Projection.
void
Vector::calc_projection(const Vector& base,
                        Vector& projection) const
{
    projection.set(base);
    projection.normalize();
    projection.mul(projection_value(base));
}

/// \brief Orthogonal decomposition.
///
/// Orthogonal decomposition - decompose the vector into projection and orthogonal component.
///
/// \param[in]  base       Base vector.
/// \param[in]  projection Projection.
/// \param[out] orthogonal Orthogonal component.
void
Vector::orthogonal_decompose(const Vector& base,
                             Vector& projection,
                             Vector& orthogonal) const
{
    calc_projection(base, projection);
    sub(*this, projection, orthogonal);
}

/// \brief Outer normal to triangle.
///
/// Calculate outer normal to the triangle.
///
/// \param[in]  a First point.
/// \param[in]  b Second point.
/// \param[in]  c Third point.
/// \param[out] r Result.
void
Vector::calc_outer_normal(const Vector& a,
                          const Vector& b,
                          const Vector& c,
                          Vector& r)
{
    Vector ba;
    Vector ca;

    sub(b, a, ba);
    sub(c, a, ca);

    cross_product(ba, ca, r);
    r.normalize();
}

/// \brief Calculate projection on plane.
///
/// \param[in]  a          First plane point.
/// \param[in]  b          Second plane point.
/// \param[in]  c          Third plane point.
/// \param[out] projection Projection.
void
Vector::calc_projection_on_plane(const Vector& a,
                                 const Vector& b,
                                 const Vector& c,
                                 Vector& projection) const
{
    Vector base, normal;

    calc_outer_normal(a, b, c, base);
    orthogonal_decompose(base, normal, projection);
}

//
// Construct other vectors.
//

/// \brief Construct orth vector - direction of triangle height.
///
/// We have two vectors: a (OA) and b (OB).
/// We have to calculate orth vector of triangle OAB height from O node to AB side.
/// Result vector is linear combination of a and b vectors and it is perpendicular to (a - b).
///
/// So we have an equation:
///
/// @f$ (\alpha \vec{a} + \beta \vec{b}, \vec{a} - \vec{b}) = 0 @f$
///
/// we may expand it:
///
/// @f$ \alpha (a_x^2 - a_xb_x + a_y^2 - a_yb_y + a_z^2 - a_zb_z)
///     = \beta (b_x^2 - a_xb_x + b_y^2 - a_yb_y + b_z^2 - a_zb_z) @f$
///
/// or:
///
/// @f$ \alpha (|\vec{a}|^2 - (\vec{a}, \vec{b})) = \beta (|\vec{b}|^2 - (\vec{a}, \vec{b})) @f$
///
/// \param[in]  a First vector.
/// \param[in]  b Second vector.
/// \param[out] r Result.
void
Vector::calc_height_dir(const Vector& a,
                        const Vector& b,
                        Vector& r)
{
    double ab = a * b;
    double a2 = a.mod2();
    double b2 = b.mod2();
    double alpha = b2 - ab;
    double beta = a2 - ab;

    // If coefficient of shortest size is negative, then we have to change direction.
    bool is_a_change = (a2 <= b2) && (alpha < 0.0);
    bool is_b_change = (b2 <= a2) && (beta < 0.0);

    // Check for change direction.
    if (is_a_change || is_b_change)
    {
        alpha = -alpha;
        beta = -beta;
    }

    linear_combination(a, alpha, b, beta, r);
    r.normalize();
}

//
// Calculate linear characterisctics.
//

/// \brief Triangle min side length.
///
/// Min side length.
///
/// \param[in] a First vector.
/// \param[in] b Seconds vector.
/// \param[in] c Third vector.
///
/// \return
/// Min side length
double
Vector::triangle_min_side_length(const Vector& a,
                                 const Vector& b,
                                 const Vector& c)
{
    double ab = a.dist_to(b);
    double ac = a.dist_to(c);
    double bc = b.dist_to(c);

    return min(min(ab, ac), bc);
}

//
// Calculate areas and volumes.
//

/// \brief Triangle area.
///
/// Triangle area.
///
/// \param[in] a First vector.
/// \param[in] b Seconds vector.
/// \param[in] c Third vector.
///
/// \return
/// Area.
double
Vector::triangle_area(const Vector& a,
                      const Vector& b,
                      const Vector& c)
{
    Vector v1, v2, p;


    sub(b, a, v1);
    sub(c, a, v2);
    cross_product(v1, v2, p);

    return 0.5 * p.mod();
}

/// \brief Tetrahedron volume.
///
/// Tetrahedron volume.
///
/// \param[in] a First vector.
/// \param[in] b Seconds vector.
/// \param[in] c Third vector.
/// \param[in] d 4th vector.
///
/// \return
/// Volume.
double
Vector::tetrahedron_volume(const Vector& a,
                           const Vector& b,
                           const Vector& c,
                           const Vector& d)
{
    Vector v1, v2, v3;

    sub(b, a, v1);
    sub(c, a, v2);
    sub(d, a, v3);

    double p = triple_product(v1, v2, v3) / 6.0;

    return abs(p);
}

/// \brief Displaced triangle volume.
///
/// Displaced triangle volume.
///
/// \param[in] ao First point of bottom triangle.
/// \param[in] bo Seconds point of bottom triangle.
/// \param[in] co Third point of bottom triangle.
/// \param[in] an First point of top triangle.
/// \param[in] bn Seconds point of top triangle.
/// \param[in] cn Third point of top triangle.
///
/// \return
/// Volume.
double
Vector::displaced_triangle_volume(const Vector& ao,
                                  const Vector& bo,
                                  const Vector& co,
                                  const Vector& an,
                                  const Vector& bn,
                                  const Vector& cn)
{
    return tetrahedron_volume(ao, bo, co, cn)
           + tetrahedron_volume(ao, bo, bn, cn)
           + tetrahedron_volume(ao, an, bn, cn);
}

/// @}

}
