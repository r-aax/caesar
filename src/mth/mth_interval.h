/// \file
/// \brief Interval declaration.
///
/// Interval declaration.

#ifndef CAESAR_MTH_INTERVAL_H
#define CAESAR_MTH_INTERVAL_H

#include "diag/diag.h"

namespace caesar
{

namespace mth
{

/// \addtogroup mth
/// @{

/// \brief Interval.
///
/// Interval.
class Interval
{

private:

    /// \brief Low value.
    ///
    /// Low value.
    double lo_ { 0.0 };

    /// \brief Hight value.
    ///
    /// High value.
    double hi_ { 0.0 };

public:

    /// \brief Default constructor.
    ///
    /// Default constructor.
    Interval()
    {
    }

    /// \brief Constructor.
    ///
    /// Constructor.
    ///
    /// \param[in] init_lo Lo value.
    /// \param[in] init_hi High value.
    Interval(double init_lo,
             double init_hi)
        : lo_(init_lo),
          hi_(init_hi)
    {
    }

    /// \brief Create interval as eps around point.
    ///
    /// Interval around point neighbourhood.
    ///
    /// \param[in] p   Point.
    /// \param[in] eps Eps.
    static Interval
    around_point(double p,
                 double eps)
    {
        return Interval(p - eps, p + eps);
    }

    /// \brief Get non negative part.
    ///
    /// Get non negative part.
    ///
    /// \return
    /// Non negative part.
    Interval
    non_neg() const
    {
        return Interval(max(lo(), 0.0), hi());
    }

    /// \brief Get non positive.
    ///
    /// Get non positive part.
    ///
    /// \return
    /// Non positive part.
    Interval
    non_pos() const
    {
        return Interval(lo(), min(hi(), 0.0));
    }

    /// \brief Get low value.
    ///
    /// Get low value.
    ///
    /// \return
    /// Low value.
    inline double
    lo() const
    {
        return lo_;
    }

    /// \brief Get high value.
    ///
    /// Get high value.
    ///
    /// \return
    /// High value.
    inline double
    hi() const
    {
        return hi_;
    }

    /// \brief Length.
    ///
    /// Get length.
    ///
    /// \return
    /// Length.
    inline double
    len() const
    {
        return hi_ - lo_;
    }

    /// \brief Check if interval real.
    ///
    /// Check interval.
    ///
    /// \return
    /// true - if interval is real,
    /// false - otherwise.
    inline bool
    is_real() const
    {
        return lo_ <= hi_;
    }
};

/// @}

}

}

#endif // !CAESAR_MTH_INTERVAL_H
