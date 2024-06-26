/// \file
/// \brief Declaration of time line.
///
/// Time line.

#ifndef UTILS_TIME_LINE_H
#define UTILS_TIME_LINE_H

#include "utils_time.h"

namespace utils
{

/// \addtogroup utils
/// @{

/// \brief Time line.
class TimeLine
{

private:

    /// \brief Start time.
    Time start;

    /// \brief Current time.
    Time current;

    /// \brief Finish time.
    Time finish;

    /// \brief Step.
    Time step;

    /// \brief Iterations count.
    int iter { 0 };

public:

    // Default constructor.
    TimeLine();

    // Constructor.
    TimeLine(double start_s,
             double finish_s,
             double step_s);

    // Destructor.
    ~TimeLine();

    // Init.
    void
    init(double start_s,
         double finih_s,
         double step_s);

    // Time in seconds.
    double
    seconds() const;

    // Time in microseconds.
    int64_t
    microseconds() const;

    // Time step.
    double
    dt() const;

    // Iteration number.
    int
    iteration() const;

    // Check if time line finished.
    bool
    is_finished() const;

    // Check if it is beginning.
    bool
    is_begin() const;

    // Move to next iteration.
    void
    next_iteration();

    // Check is time multiple.
    bool
    is_time_multiple(const Time& t) const;

    // Check if iteration multiple.
    bool
    is_iteration_multiple(int f) const;

    // Pulse.
    void
    pulse();

    // Timestamp string.
    string
    timestamp_string();
};

/// @}

}

#endif // UTILS_TIME_LINE_H
