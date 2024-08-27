/// \file
/// \brief Some functions for some system features.
///
/// System utilities.

#ifndef CAESAR_UTILS_SYSTEM_H
#define CAESAR_UTILS_SYSTEM_H

#include <cstdint>

namespace caesar
{

namespace utils
{

/// \addtogroup utils
/// @{

// Hash function for double.
uint64_t
double_hash(double x);

/// @}

}

}

#endif // !CAESAR_UTILS_SYSTEM_H
