/// \file
/// \brief Implementation of time line.
///
/// Implementation of time line.

#include "utils_time_line.h"

#include <iostream>

namespace utils
{

/// \addtogroup utils
/// @{

/// \brief Default constructor.
TimeLine::TimeLine()
{
}

/// \brief Constructor.
///
/// Constructor.
///
/// \param[in] start_s  Start time.
/// \param[in] finish_s Finish time.
/// \param[in] step_s   Step time.
TimeLine::TimeLine(double start_s,
                   double finish_s,
                   double step_s)
{
    init(start_s, finish_s, step_s);
}

/// \brief Destructor.
TimeLine::~TimeLine()
{
}

/// \brief Init.
///
/// Init from times.
///
/// \param[in] start_s  Start time.
/// \param[in] finish_s Finish time.
/// \param[in] step_s   Step time.
void
TimeLine::init(double start_s,
               double finish_s,
               double step_s)
{
    start.init(start_s);
    current.init(start_s);
    finish.init(finish_s);
    step.init(step_s);
}

/// \brief Time in seconds.
///
/// Time is seconds.
///
/// \return
/// Time in seconds.
double
TimeLine::seconds() const
{
    return current.seconds();
}

/// \brief Time in microseconds.
///
/// Time in microseconds.
///
/// \return
/// Time in microseconds.
int64_t
TimeLine::microseconds() const
{
    return current.microseconds();
}

/// \brief Time step.
///
/// Time step in seconds.
///
/// \return
/// Time step in seconds.
double
TimeLine::dt() const
{
    return step.seconds();
}

/// \brief Iteration number.
///
/// Get iteration number.
///
/// \return
/// Iteration number.
int
TimeLine::iteration() const
{
    return iter;
}

/// \brief Check if time line finished.
///
/// Check if time line finished.
///
/// \return
/// true - if time line is finished,
/// false - otherwise.
bool
TimeLine::is_finished() const
{
    return current.microseconds() >= finish.microseconds();
}

/// \brief Check if it is beginning.
///
/// Check for begining.
///
/// \return
/// true - if it is begin of time line,
/// false - otherwise.
bool
TimeLine::is_begin() const
{
    return current.microseconds() == start.microseconds();
}

/// \brief Move to next iteration.
///
/// Move to next iteration.
void
TimeLine::next_iteration()
{
    ++iter;
    current.inc_microseconds(step.microseconds());
}

/// \brief Check is time multiple.
///
/// Check if time line is multiple to other time.
///
/// \return
/// true - time is multiple to other time,
/// false - otherwise.
bool
TimeLine::is_time_multiple(const Time& t) const
{
    if (t.is_finite())
    {
        return (current.microseconds() % t.microseconds()) == 0;
    }
    else
    {
        return false;
    }
}

/// \brief Check if iteration multiple.
///
/// Check if iteration is multiple.
///
/// \return
/// true - is iteration is multiple of the argument,
/// false - otherwise.
bool
TimeLine::is_iteration_multiple(int f) const
{
    return (iter % f) == 0;
}

/// \brief Pulse.
///
/// Say pulse to screen.
void
TimeLine::pulse()
{
    cout << "pulse : time = " << seconds() << " s, iteration = " << iteration() << endl;
}

/// \brief Timestamp string.
///
/// Get timestamp string.
///
/// \return
/// Timestamp string.
string
TimeLine::timestamp_string()
{
    return current.timestamp_string();
}

/// @}

}
