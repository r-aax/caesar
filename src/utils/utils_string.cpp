/// \file
/// \brief Operations with strings implementation.
///
/// Additional operations with strings.

#include "utils_string.h"

namespace utils
{

/// \addtogroup utils
/// @{

/// \brief Find word.
///
/// Find next word (spaces are ignored).
///
/// \param[in]  s     String.
/// \param[in]  start Start position.
/// \param[out] p     Position of found substring.
/// \param[out] len   Length of found substring.
///
/// \result
/// true - if substring is found,
/// false - otherwise.
bool
find_word(const string& s,
          int start,
          int& p,
          int& len)
{
    const string delims { " \n\r\t" };

    // Find first good character.
    p = s.find_first_not_of(delims, start);

    // If not found there is no word.
    if (p == string::npos)
    {
        return false;
    }

    // Find end of word.
    auto p2 = s.find_first_of(delims, p + 1);

    if (p2 == string::npos)
    {
        len = s.size() - p;
    }
    else
    {
        len = p2 - p;
    }

    return true;
}

/// \brief Find next substring in double quotes.
///
/// Find next substring in double quuotes ("substring").
///
/// \param[in]  s     String.
/// \param[in]  start Start position for searching.
/// \param[out] p     Position of found substring.
/// \param[out] len   Length of found substring.
///
/// \result
/// true - if substring is found,
/// false - otherwise.
bool
find_substr_in_double_quotes(const string& s,
                             int start,
                             int& p,
                             int& len)
{
    // Find first double quote position.
    p = s.find('"', start);

    // If first double quote is not found, there is no substring.
    if (p == string::npos)
    {
        return false;
    }

    // Ignore double quote itself.
    ++p;

    // Find second double quote position.
    auto p2 = s.find('"', p + 1);

    // If second quote is not found there is no substring.
    if (p2 == string::npos)
    {
        return false;
    }

    // Ignore double quote itself.
    --p2;

    // Substring is found.
    len = p2 - p + 1;

    return true;
}

/// \brief Get integer value after eq char.
///
/// Get integer from string after "=" character.
///
/// \param[in] s String.
///
/// \return
/// Integer value.
int
get_int_from_str_after_eq_sign(const string& s)
{
    return stoi(s.substr(s.find('=') + 1));
}

/// \brief Find integer interval bounds.
///
/// Find integer bounds of interval in string.
///
/// \param[in]  s  String.
/// \param[out] lo Lower bound value.
/// \param[out] hi Higher bound value.
///
/// \return
/// true - if bounds are found,
/// false - otherwise.
bool
find_interval_int_bounds_in_str(const string& s,
                                int& lo,
                                int& hi)
{
    // Position of open bracket.
    auto open_b_p = s.find('[');

    // If open bracket is not found, there is no interval.
    if (open_b_p == string::npos)
    {
        return false;
    }

    // Position of minus.
    auto minus_p = s.find('-', open_b_p + 1);

    // If minus is not found, there is no interval.
    if (minus_p == string::npos)
    {
        return false;
    }

    // Position of close bracket.
    auto close_b_p = s.find(']', minus_p + 1);

    // If second bracket is not found, there is no interval.
    if (close_b_p == string::npos)
    {
        return false;
    }

    // All positions are found.
    lo = stoi(s.substr(open_b_p + 1, minus_p - open_b_p - 1));
    hi = stoi(s.substr(minus_p + 1, close_b_p - minus_p - 1));

    return true;
}

/// @}

}
