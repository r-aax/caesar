/// \file
/// \brief Timer implementation.
///
/// Timer implementation.

#include "utils_timer.h"
#include "utils_includes.h"
 
namespace utils
{

/// \addtogroup utils
/// @{

/// \brief Default constructor.
///
/// Default constructor.
Timer::Timer()
{
}

/// \brief Default destructor.
///
/// Default destructor.
Timer::~Timer()
{
}

/// \brief Clear.
///
/// Clear timer.
void
Timer::clear()
{
    total = 0.0;
}

/// \brief Start timer.
///
/// Start timer.
void
Timer::start()
{
    if (!is_active())
    {
        start_point = omp_get_wtime();
    }
}

/// \brief Stop timer.
///
/// Stop timer.
void
Timer::stop()
{
    if (is_active())
    {
        total += (omp_get_wtime() - start_point);
        start_point = -1.0;
    }
}

/// \brief Check if active.
///
/// \return
/// true - if timer is active,
/// false - otherwise.
bool
Timer::is_active() const
{
    return start_point > 0.0;
}

/// \brief Get.
///
/// Get value of timer.
///
/// \return
/// Value of timer.
double
Timer::get() const
{
    return total + (is_active() ? (omp_get_wtime() - start_point) : 0.0);
}

///@}

}
