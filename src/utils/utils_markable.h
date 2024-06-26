/// \file
/// \brief Markable object declaration.
///
/// Markable object.

#ifndef UTILS_MARKABLE_H
#define UTILS_MARKABLE_H

namespace utils
{

/// \addtogroup utils
/// @{

/// \brief Markable object.
class Markable
{

private:

    /// \brief Mark.
    int mark;

public:

    /// \brief Default constructor.
    Markable()
    {
    }

    /// \brief Default destructor.
    ~Markable()
    {
    }

    /// \brief Set mark.
    ///
    /// Set mark.
    ///
    /// \param[in] m Mark.
    inline void
    set_mark(int m)
    {
        mark = m;
    }

    /// \brief Get mark.
    ///
    /// \return
    /// Mark.
    inline int
    get_mark() const
    {
        return mark;
    }
};

/// @}

}

#endif // UTILS_MARKABLE_H
