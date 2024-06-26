/// \file
/// \brief Module for work with time.
///
/// Work with time in seconds and microseconds.

#ifndef UTILS_TIME_H
#define UTILS_TIME_H

#include "includes.h"

namespace utils
{

/// \addtogroup utils
/// @{

/// \brief Time.
class Time
{

public:

    /// \brief Count of chars in timestamp.
    static constexpr size_t timestamp_symbols_count { 12 };

private:

    /// \brief Million.
    static constexpr double million { 1000000.0 };

    /// \brief Time in seconds.
    double s { 0.0 };

    /// \brief Time in microseconds.
    int64_t ms { 0 };

public:

    // Default constructor.
    Time();

    // Constructor.
    Time(double s_);

    // Destructor.
    ~Time();

    // Init.
    void
    init(double s_);

    // Time in seconds.
    double
    seconds() const;

    // Time in microseconds.
    int64_t
    microseconds() const;

    // Increment time in microseconds.
    void
    inc_microseconds(int64_t inc);

    // Check if time finite.
    bool
    is_finite() const;

    // Timestamp strings.
    string
    timestamp_string();

    // Check string has timestamp.
    static bool
    has_timestamp(const string& s);

    // Get time from timestamp.
    static double
    get_seconds_from_timestamp(const string& s);
};

/// @}

}

#endif // UTILS_TIME_H
