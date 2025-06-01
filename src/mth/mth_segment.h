/// \file
/// \brief Segment declaration.
///
/// Interval declaration.

#ifndef CAESAR_MTH_SEGMENT_H
#define CAESAR_MTH_SEGMENT_H

#include "diag/diag.h"
#include "mth_basics.h"

namespace caesar
{

namespace mth
{

/// \addtogroup mth
/// @{

/// \brief Segment.
///
/// Segment.
class Segment
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
    Segment()
    {
    }

    /// \brief Copy constructor.
    ///
    /// Copy constructor.
    ///
    /// \param[in] s Segment.
    Segment(const Segment& s)
        : Segment(s.lo(), s.hi())
    {
    }

    /// \brief Constructor.
    ///
    /// Constructor.
    ///
    /// \param[in] init_lo Lo value.
    /// \param[in] init_hi High value.
    Segment(double init_lo,
            double init_hi)
        : lo_(init_lo),
          hi_(init_hi)
    {
    }

    /// \brief Create segment as eps around point.
    ///
    /// Segment around point neighbourhood.
    ///
    /// \param[in] p   Point.
    /// \param[in] eps Eps.
    static Segment
    around_point(double p,
                 double eps)
    {
        return Segment(p - eps, p + eps);
    }

    /// \brief Get non negative part.
    ///
    /// Get non negative part.
    ///
    /// \return
    /// Non negative part.
    Segment
    non_neg() const
    {
        return Segment(max(lo(), 0.0), hi());
    }

    /// \brief Get non positive.
    ///
    /// Get non positive part.
    ///
    /// \return
    /// Non positive part.
    Segment
    non_pos() const
    {
        return Segment(lo(), min(hi(), 0.0));
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

    /// \brief Check if segment real.
    ///
    /// Check segment.
    ///
    /// \return
    /// true - if segmetn is real,
    /// false - otherwise.
    inline bool
    is_real() const
    {
        return lo_ <= hi_;
    }

    /// \brief Check if point lays on segment.
    ///
    /// Check if point lays on segment.
    ///
    /// \param[in] p Point.
    ///
    /// \return
    /// true - if point on segment,
    /// false - otherwise.
    inline bool
    contains(double p) const
    {
        return in_bounds<double>(p, lo_, hi_);
    }
};

/// @}

}

}

#endif // !CAESAR_MTH_SEGMENT_H
