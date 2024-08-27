/// \file
/// \brief Operations with strings.
///
/// Additional operations with strings.

#ifndef UTILS_STRING_H
#define UTILS_STRING_H

#include <string>
#include <vector>

using namespace std;

namespace utils
{

/// \addtogroup utils
/// @{

// Check if string starts with prefix.
bool
str_starts_with(const string& s,
                const string& pre);

// Find word.
bool
find_word(const string& s,
          size_t start,
          const string& delims,
          size_t& p,
          size_t& len);

// Find word.
bool
find_word(const string& s,
          size_t start,
          size_t& p,
          size_t& len);

// Split by words.
void
split_into_words(const string& s,
                 const string& delims,
                 vector<string>& r,
                 bool is_clear_r = true);

// Find next substring in double quotes.
bool
find_substr_in_double_quotes(const string& s,
                             size_t start,
                             size_t& p,
                             size_t& len);

// Get integer value after eq char.
int
get_int_from_str_after_eq_sign(const string& s);

// Find integer interval bounds.
bool
find_interval_int_bounds_in_str(const string& s,
                                size_t& lo,
                                size_t& hi);

/// @}

}

#endif // UTILS_STRING_H
