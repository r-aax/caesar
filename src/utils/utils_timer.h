/// \file
/// \brief Timer declaration.
///
/// Timer declaration.

#ifndef UTILS_TIMER_H
#define UTILS_TIMER_H

namespace utils
{

/// \addtogroup utils
/// @{

/// \brief Timer.
class Timer
{

private:

    /// \brief Value.
    double total { 0.0 };

    /// \brief Start point.
    ///
    /// If start point is negative, it means timer is not active.
    /// If start point is not negative, it means timer is active.
    double start_point { -1.0 };

public:

    // Default constructor.
    Timer();

    // Default destructor.
    ~Timer();

    // Clear.
    void
    clear();

    // Start timer.
    void
    start();

    // Stop timer.
    void
    stop();

    // Check if active.
    bool
    is_active() const;

    // Get.
    double
    get() const;
};

/// @}

}

#endif // UTILS_TIMER_H
