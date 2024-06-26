/// \file
/// \brief Declaration of bits manipulation functions.
///
/// Declaration of bits manipulation functions
/// bit manipulation functions work with unsigned int type.

#ifndef MTH_BITS_H
#define MTH_BITS_H

#include "utils/utils.h"

namespace mth
{

/// \addtogroup mth
/// @{

// Least bit with value 0.
int
least_bit_0(uint32_t x);

// Least bit with value 1.
int
least_bit_1(uint32_t x);

/// @}

}

#endif // !MTH_BITS_H
