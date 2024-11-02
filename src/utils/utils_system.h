/// \file
/// \brief Some functions for some system features.
///
/// System utilities.

#ifndef CAESAR_UTILS_SYSTEM_H
#define CAESAR_UTILS_SYSTEM_H

#include <cstdint>
#include <string>

using namespace std;

namespace caesar
{

namespace utils
{

/// \addtogroup utils
/// @{

// Hash function for double.
uint64_t
double_hash(double x);

// Check if file exists.
bool
is_file_exist(string fn);

// Check if directory exists.
bool
is_directory_exist(string dn);

/// @}

}

}

#endif // !CAESAR_UTILS_SYSTEM_H
