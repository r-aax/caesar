/// \file
/// \brief Implementation of class for work with time.
///
/// Implementation of class for work with time.

#include "utils_time.h"
#include "includes.h"

namespace utils
{

/// \addtogroup utils
/// @{

/// \brief Default constructor.
///
/// Default constructor.
Time::Time()
{
}

/// \brief Constructor.
///
/// Constructor from time.
///
/// \param[in] s_ Time in seconds.
Time::Time(double s_)
{
    init(s_);
}

/// \brief Destructor.
Time::~Time()
{
}

/// \brief Init.
///
/// Init from time.
///
/// \param[in] s_ Time in seconds.
void
Time::init(double s_)
{
    s = s_;

    if (isfinite(s))
    {
        ms = static_cast<int64_t>(s * million);
    }
    else
    {
        ms = 0;
    }
}

/// \brief Time in seconds.
///
/// Get time in seconds.
///
/// \return
/// Time in seconds.
double
Time::seconds() const
{
    return s;
}

/// \brief Time in microseconds.
///
/// Get time in microseconds.
///
/// \return
/// Time in microseconds.
int64_t
Time::microseconds() const
{
    return ms;
}

/// \brief Increment time in microseconds.
///
/// Increment time in microseconds.
///
/// \param[in] inc Time for increment.
void
Time::inc_microseconds(int64_t inc)
{
    ms += inc;
    s = static_cast<double>(ms) / million;
}

/// \brief Check if time finite.
///
/// \return
/// true - if time is finite,
/// false - otherwize.
bool
Time::is_finite() const
{
    return isfinite(s);
}

/// \brief Timestamp strings.
///
/// Get timestamp string.
///
/// \return
/// Timestamp string.
string
Time::timestamp_string()
{
    string s = to_string(ms);

    return string(timestamp_symbols_count - s.size(), '0') + s;
}

/// \brief Check string has timestamp.
///
/// \param[in] s String.
///
/// \return
/// true - if string has timestamp,
/// false - otherwise.
bool
Time::has_timestamp(const string& s)
{
    size_t n = s.size();

    if (n < timestamp_symbols_count + 2)
    {
        // We need 1 additional symbol for '_' and 1 for name.
        return false;
    }

    // Check for digits.
    for (size_t i = 0; i < timestamp_symbols_count; ++i)
    {
        if (!isdigit(s[n - 1 - i]))
        {
            return false;
        }
    }

    // Check for underscore.
    if (s[n - 1 - timestamp_symbols_count] != '_')
    {
        return false;
    }

    return true;
}

/// \brief Get time from timestamp.
///
/// \param[in] s String.
///
/// \return
/// Time in seconds.
double
Time::get_seconds_from_timestamp(const string& s)
{
    size_t n = s.size();
    string ss = s.substr(n - timestamp_symbols_count);

    return static_cast<double>(stoll(ss)) / million;
}

/// @}

}
