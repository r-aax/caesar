/// \file
/// \brief Operations with strings.
///
/// Additional operations with strings.

#ifndef UTILS_STRING_H
#define UTILS_STRING_H

#include "utils_includes.h"

namespace utils
{

/// \addtogroup utils
/// @{

// Find word.
bool
find_word(const string& s,
          int start,
          int& p,
          int& len);

// Find next substring in double quotes.
bool
find_substr_in_double_quotes(const string& s,
                             int start,
                             int& p,
                             int& len);

// Get integer value after eq char.
int
get_int_from_str_after_eq_sign(const string& s);

// Find integer interval bounds.
bool
find_interval_int_bounds_in_str(const string& s,
                                int& lo,
                                int& hi);

/// @}

}

#endif // UTILS_STRING_H
