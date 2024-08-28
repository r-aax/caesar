/// \file
/// \brief Mathematical basics.
///
/// Basic data and functions for math.

#ifndef CAESAR_MTH_BASICS_H
#define CAESAR_MTH_BASICS_H

// The only place for <cmath> include.
#include <cmath>

// The only place for <algorithm> include.
#include <algorithm>

#include <vector>
#include <utility>

using namespace std;

/// \addtogroup mth
/// @{

/// \brief Kilo prefix (1000, 10^3).
#define MTH_KILO 1.0e+3

/// \brief Mega prefix (1000000, 10^6).
#define MTH_MEGA 1.0e+6

/// \brief Milli prefix (0.001, 10^-3).
#define MTH_MILLI 1.0e-3

/// \brief Micro prefix (0.000001, 10^-6).
#define MTH_MICRO 1.0e-6

/// \brief One hundred percent.
#define HUNDRED_PERCENTS 100.0

/// @}

namespace caesar
{

namespace mth
{

/// \addtogroup mth
/// @{

/// \brief Small value.
const double Eps { 1.0e-12 };

/// \brief Pi.
const double Pi { 3.14159265358979323846264338328 };

/// \brief Degrees count in one radian.
const double OneRadianDegrees { 180.0 / Pi };

/// \brief Order.
enum class Order
{
    /// \brief Less than.
    Lt,

    /// \brief Inside.
    In = Lt,

    /// \brief Equal.
    Eq,

    /// \brief On onject.
    On = Eq,

    /// \brief Greater than.
    Gt,

    /// \brief Outside.
    Out = Gt,

    /// \brief Undefined value.
    Unknown
};

/// \brief Check if number is even.
///
/// Check if number is even.
///
/// \tparam    T Integer type.
/// \param[in] x Number.
///
/// \return
/// true - if number is even,
/// false - otherwise.
template<typename T>
bool
is_even(T x)
{
    return (x & 0x1) == 0;
}

/// \brief Check if number is odd.
///
/// Check if number is odd.
///
/// \tparam    T Integer type.
/// \param[in] x Number.
///
/// \return
/// true - if number is odd,
/// false - otherwise.
template<typename T>
bool
is_odd(T x)
{
    return (x & 0x1) == 1;
}

/// \brief Check if near.
///
/// Check if near.
///
/// \param[in] x   First value.
/// \param[in] y   Second value.
/// \param[in] eps Small value.
///
/// \return
/// true - if near,
/// false - otherwise.
inline bool
is_near(double x,
        double y,
        double eps = Eps)
{
    return fabs(x - y) <= eps;
}

/// \brief Check if two doubles are equal.
///
/// Check equal of doubles.
///
/// \param[in] x First value.
/// \param[in] y Second value.
///
/// \return
/// true - if values are near,
/// false - otherwise.
inline bool
is_eq(double x,
      double y)
{
    return is_near(x, y, Eps);
}

/// \brief Check if value is zero.
///
/// Check if value is zero.
///
/// \param[in] x Value.
///
/// \return
/// true - if value is zero,
/// false - otherwise.
inline bool
is_zero(double x)
{
    return is_eq(x, 0.0);
}

/// \brief Sign.
///
/// Sign of value.
///
/// \tparam T     Type.
/// \param [in] x Value.
///
/// \return
/// Sign.
template<typename T>
T
sgn(T x)
{
    T z = static_cast<T>(0);

    if (x > z)
    {
        return static_cast<T>(1);
    }
    else if (x < z)
    {
        return static_cast<T>(-1);
    }
    else
    {
        return z;
    }
}

/// \brief Cube.
///
/// Value in cube.
///
/// \tparam T     Type.
/// \param [in] x Value.
///
/// \return
/// Cube value.
template<typename T>
T
cube(T x)
{
    return x * x * x;
}

/// \brief Detecting including value into range.
///
/// \tparam    T Template type.
/// \param[in] x Checked value.
/// \param[in] l Low bound.
/// \param[in] h High bound.
///
/// \return
/// true - if vaue is in bound,
/// false - otherwise.
template<typename T>
bool
in_bounds(T x,
          T l,
          T h)
{
    return (x >= l) && (x <= h);
}

/// \brief Detecting inclusion value into range set by pair.
///
/// \tparam    T Template type.
/// \param[in] x Checked value.
/// \param[in] p Pair.
///
/// \return
/// true - if vaue is in bound,
/// false - otherwise.
template<typename T>
bool
in_bounds(T x,
          const pair<T, T>& p)
{
    return in_bounds(x, p.first, p.second);
}

/// \brief Detecting inclusion value into range set by vector of two elements.
///
/// \tparam    T Template type.
/// \param[in] x Checked value.
/// \param[in] v Vector.
///
/// \return
/// true - if vaue is in bound,
/// false - otherwise.
template<typename T>
bool
in_bounds(T x,
          const vector<T>& v)
{
    return in_bounds(x, v[0], v[1]);
}

/// \brief Bringing the value into bounds.
///
/// Bring value to bounds.
///
/// \tparam T     Type of numbes.
/// \param [in] x Number.
/// \param [in] l Low bound.
/// \param [in] h High bound.
///
/// \return
/// Number in bounds.
template<typename T>
T
to_bounds(T x,
          T l,
          T h)
{
    return (x < l) ? l : ((x > h) ? h : x);
}

// Pythagorian theorem for 3 values.
double
pyth(double a,
     double b,
     double c);

/// \brief Convert degrees to radians.
///
/// Convert degrees to radians.
///
/// \param[in] d Degrees.
///
/// \return
/// Radians.
inline double
degrees_to_radians(double d)
{
    return d / OneRadianDegrees;
}

/// \brief Convert radians to degrees.
///
/// Convert radians to degrees.
///
/// \param[in] r Radians.
///
/// \return
/// Degrees.
inline double
radians_to_degrees(double r)
{
    return r * OneRadianDegrees;
}

// Random integer value in range.
int
randint(int lo,
        int hi);

/// @}

}

}

#endif // !CAESAR_MTH_BASICS_H
