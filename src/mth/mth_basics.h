///
/// @file
/// @brief Определение математических примитивов.
///

#ifndef MTH_BASICS_H
#define MTH_BASICS_H

#include "mth_sle.h"
#include "utils/utils.h"

/// @addtogroup mth
/// @{

/// @brief Приставка "кило".
#define MTH_KILO 1.0e+3

/// @brief Приставка "мега".
#define MTH_MEGA 1.0e+6

/// @brief Приставка "милли".
#define MTH_MILLI 1.0e-3

/// @brief Приставка "микро".
#define MTH_MICRO 1.0e-6

/// @brief 100 процентов.
#define HUNDRED_PERCENTS 100.0

/// @}

namespace mth
{

/// @addtogroup mth
/// @{

/// \brief Small value.
const double Eps { 1.0e-10 };

/// \brief Pi.
const double Pi { 3.14159265358979323846264338328 };

/// \brief Degrees count in one radian.
const double OneRadianDegrees { 180.0 / Pi };

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
    return abs(x - y) <= eps;
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

/// @brief Порядок.
enum class Order
{
    /// @brief Значение меньше.
    Lt,

    /// @brief Значение внутри.
    In = Lt,

    /// @brief Значение равно.
    Eq,

    /// @brief Значение на.
    On = Eq,

    /// @brief Значение больше.
    Gt,

    /// @brief Значение вне.
    Out = Gt,

    /// @brief Неизвестное значение.
    Unknown
};

/// @brief Знак числа.
///
/// @tparam T - Тип числа.
/// @param [in] x - Число.
///
/// @return
/// Знак числа.
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

/// @brief Куб значения.
///
/// @tparam T - Тип значения.
/// @param [in] x - Значение.
///
/// @return
/// Куб значения.
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

/// @brief Bringing the value into bounds.
///
/// @tparam T - Type of numbes.
/// @param [in] x - Number.
/// @param [in] l - Low bound.
/// @param [in] h - High bound.
///
/// @return
/// Number in bounds.
template<typename T>
T
to_bounds(T x,
          T l,
          T h)
{
    return (x < l) ? l : ((x > h) ? h : x);
}

// Применение формулы Пифагора в трехмерном случае.
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
/// \param[n] r Radians.
///
/// \return
/// Degrees.
inline double
radians_to_degrees(double r)
{
    return r * OneRadianDegrees;
}

/// @}

}

#endif // !MTH_BASICS_H
