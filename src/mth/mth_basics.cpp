/// \file
/// \brief Mathematical primitives implementation.
///
/// Mathematical primitives.

#include "mth_basics.h"

// Only place for <random> include.
#include <random>

namespace caesar
{

namespace mth
{

/// \addtogroup mth
/// @{

/// \brief Pythagorian theorem.
///
/// Hypotenuse calculation by pythagorian theorem.
///
/// \param[in] a Distance along OX axis.
/// \param[in] b Distance along OY axis.
/// \param[in] c Distance along OZ axis.
///
/// \return
/// Hypotenuse length.
double
pyth(double a,
     double b,
     double c)
{
    return sqrt(a * a + b * b + c * c);
}

/// \brief Random integer value in range.
///
/// Random integer value in range (lo <= x <= hi).
///
/// \param[in] lo Lower bound.
/// \param[in] hi High bound.
///
/// \return
/// Random value.
int
randint(int lo,
        int hi)
{
    return lo + (rand() % (hi - lo + 1));
}

/// @}

}

}
