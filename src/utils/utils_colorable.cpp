/// \file
/// \brief Colorable object implementation.
///
/// Colorable object implementation.

#include "utils_colorable.h"

#include "diag/diag.h"
#include "mth/mth.h"

namespace caesar
{

namespace utils
{

/// \addtogroup utils
/// @{

/// \brief Default constructor.
///
/// Default constructor.
Colorable::Colorable()
{
}

/// \brief Default destructor.
///
/// Default destructor.
Colorable::~Colorable()
{
}

/// \brief Clear.
///
/// Clear all colors.
void
Colorable::clear()
{
    mask = 0x0;
}

/// \brief Clear color.
///
/// Clear particular color.
///
/// \param[in] i Color number.
void
Colorable::clear(int i)
{
    DEBUG_CHECK_ERROR((i >= 0) && (i < colors_count), "wrong color number");

    mask &= (~(1u << i));
}

/// \brief Paint.
///
/// Paint particular color.
///
/// \param[in] i Color number.
void
Colorable::paint(int i)
{
    DEBUG_CHECK_ERROR((i >= 0) && (i < colors_count), "wrong color number");

    mask |= (1u << i);
}

/// \brief Check if painted.
///
/// Check if object is painted with given color.
///
/// \param[in] i Color number.
///
/// \return
/// true - if object is painted with this color,
/// false - otherwise.
bool
Colorable::is_painted(int i) const
{
    DEBUG_CHECK_ERROR((i >= 0) && (i < colors_count), "wrong color number");

    return (mask & (1u << i)) != 0x0;
}

/// \brief Get first free color.
///
/// Get first free color.
///
/// \return
/// First free color number or -1 if all colors are in use.
int
Colorable::first_free_color() const
{
    return mth::least_bit_0(mask);
}

/// @}

}

}
