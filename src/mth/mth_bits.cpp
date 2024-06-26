/// \file
/// \brief Implementation of bits manipulation functions.
///
/// Implementation of bits manipulation functions.

#include "mth_bits.h"

namespace mth
{

/// \addtogroup mth
/// @{

/// \brief Least bit with value 0.
///
/// Index of least bit 0.
/// If there is not such bit - return -1.
///
/// \param[in] x Value.
///
/// \return
/// Least 0 bit or -1.
int
least_bit_0(uint32_t x)
{
    return least_bit_1(~x);
}

/// \brief Least bit with value 1.
///
/// Index of least bit 1.
/// If there is not such bit - return -1.
///
/// \param[in] x Value.
///
/// \return
/// Least 1 bit or -1.
int
least_bit_1(uint32_t x)
{
    int off { 0 };
    static int m[] { -1, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0 };

    // Analyze bits chunks of size 4.
    while (x)
    {
        uint32_t chunk { x & 0xF };
        int pos { m[chunk] };

        if (pos >= 0)
        {
            return off + pos;
        }

        x >>= 4;
        off += 4;
    }

    // No 1 bits found.
    return -1;
}

/// @}

}
