/// \file
/// \brief Colorable object declaration.
///
/// Colorable object declaration.

#ifndef UTILS_COLORABLE_H
#define UTILS_COLORABLE_H

#include "utils_includes.h"

namespace utils
{

/// \addtogroup utils
/// @{

/// \brief Colorable object.
class Colorable
{

private:

    /// \brief Colors mask.
    int32_t mask { 0x0 };

    /// \brief Count of colors.
    const int colors_count { sizeof(int32_t) * 8 };

public:

    // Default constructor.
    Colorable();

    // Default destructor.
    ~Colorable();

    // Clear.
    void
    clear();

    // Clear color.
    void
    clear(int i);

    // Paint.
    void
    paint(int i);

    // Check if painted.
    bool
    is_painted(int i) const;

    // Get first free color.
    int
    first_free_color() const;
};

/// @}

}

#endif // UTILS_COLORABLE_H
