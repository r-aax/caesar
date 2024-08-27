/// \file
/// \brief System utilities implementation.
///
/// System utilities implementation.

#include "utils_system.h"

namespace caesar
{

namespace utils
{

/// \addtogroup utils
/// @{

/// \brief Hash function for double.
///
/// Hash function is just unsigned 64-bit int representation.
///
/// \param[in] x Double number.
///
/// \return
/// Hash value.
uint64_t
double_hash(double x)
{
    union
    {
        double d;
        uint64_t i;
    }
    u;

    u.d = x;

    return u.i;
}

/// @}

}

}
