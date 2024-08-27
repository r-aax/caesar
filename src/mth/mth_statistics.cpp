/// \file
/// \brief Statistics functions implementation.

#include "mth_statistics.h"

#include <numeric>

namespace mth
{

/// \addtogroup mth
/// @{

/// \brief Vector sum.
///
/// Sum of vector elements.
///
/// \param[in] v Vector of doubles.
///
/// \return
/// Sum of vector elements.
double
sum(const vector<double>& v)
{
    return accumulate(v.begin(), v.end(), 0.0);
}

/// \brief Vector mean.
///
/// Mean of vector elements.
///
/// \param[in] v Vector of doubles.
///
/// \return
/// Mean of vector elements.
double
mean(const vector<double>& v)
{
    size_t s = v.size();

    return (s == 0) ? 0.0 : (sum(v) / static_cast<double>(s));
}

/// @}

}
