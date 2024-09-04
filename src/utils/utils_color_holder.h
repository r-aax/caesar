/// \file
/// \brief Class that can hold single color.
///
/// Class that can hold single color.

#ifndef CAESAR_UTILS_COLOR_HOLDER_H
#define CAESAR_UTILS_COLOR_HOLDER_H

namespace caesar
{

namespace utils
{

/// \addtogroup utils
/// @{

/// \brief Class holds single color.
///
/// Class holds single color.
class ColorHolder
{

private:

    /// \brief Color.
    int color { 0 };

public:

    /// \brief Get color.
    ///
    /// Get color.
    ///
    /// \return
    /// Color.
    inline int
    get_color() const
    {
        return color;
    }

    /// \brief Set color.
    ///
    /// Set color.
    ///
    /// \param[in] c Color.
    inline void
    set_color(int c)
    {
        color = c;
    }

};

/// @}

}

}

#endif // !CAESAR_UTILS_COLOR_HOLDER_H
