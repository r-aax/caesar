/// \file
/// \brief Colorable object declaration.
///
/// Colorable object declaration.

#ifndef CAESAR_UTILS_COLORABLE_H
#define CAESAR_UTILS_COLORABLE_H

#include <stdlib.h>
#include <cstdint>

namespace caesar
{

namespace utils
{

/// \addtogroup utils
/// @{

/// \brief Colorable object.
class Colorable
{

private:

    /// \brief Count of colors.
    static constexpr int colors_count { static_cast<int>(sizeof(uint32_t) * 8) };

    /// \brief Colors mask.
    uint32_t mask { 0x0 };

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

}

#endif // !CAESAR_UTILS_COLORABLE_H
