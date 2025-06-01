/// \file
/// \brief Declaration of function defined on segment.
///
/// Function on segment.

#ifndef CAESAR_MTH_SEGMENT_FUNCTION_H
#define CAESAR_MTH_SEGMENT_FUNCTION_H

#include "utils/utils.h"
#include "mth_functions.h"
#include "mth_basics.h"
#include "mth_segment.h"

namespace caesar
{

namespace mth
{

/// \addtogroup mth
/// @{

/// \brief Segment function pull in type.
///
/// Type of choosing next point while solving nonlinear equation.
enum class SegmentFunctionPullInType
{
    /// \brief Pull in by bisection.
    ///
    ///     lo         p         hi
    ///     *----------*----------*
    Bisection,

    /// \brief Pull in by chords method.
    ///
    ///                          *
    ///                       /  |
    ///                    /     |
    ///     lo       p  /        |
    ///     *--------*-----------*
    ///     |     /             hi
    ///     |  /
    ///     *
    Chords,

    /// \brief Undefined.
    Undefined
};

/// \brief Function on segment.
class SegmentFunction
{

private:

    /// \brief Function.
    ///
    /// 1-dimension function.
    Function1D f;

    /// \brief Additional data.
    ///
    /// Arbitrary data.
    void* data;

    /// \brief Low bound of segment and function value in it.
    ///
    /// Low pair of argument-value.
    pair<double, double> lo;

    /// \brief High bound of segment and function value in it.
    ///
    /// Hight pair of argument-value.
    pair<double, double> hi;

    // Calculate bisection next point.
    void
    calc_bisection_next_point(pair<double, double>& p);

    // Calculate next point for chords method.
    void
    calc_chords_next_point(pair<double, double>& p);

public:

    // Default constructor.
    SegmentFunction(Function1D f_,
                    void* data_,
                    Segment segment);

    // Default destructor.
    ~SegmentFunction();

    /// \brief Length of the segment.
    ///
    /// Length of the segment.
    ///
    /// \return
    /// Length of the segment.
    double
    segment_length() const
    {
        return hi.first - lo.first;
    }

    /// \brief Get segment.
    ///
    /// Get segment.
    ///
    /// \return
    /// Segment.
    inline Segment
    get_segment()
    {
        return Segment(lo.first, hi.first);
    }

    /// \brief Check if argument on segment.
    ///
    /// Check if argument on segment.
    ///
    /// \param[in] x Argument.
    ///
    /// \return
    /// true - if argument on segment,
    /// false - otherwise.
    inline bool
    is_arg_on_segment(double x) const
    {
        return in_bounds<double>(x, lo.first, hi.first);
    }

    // Init function values on segment ends.
    void
    init_segment_ends_function_values();

    // Init segment ends by from inner point.
    void
    init_segment_ends_from_inner_point(const pair<double, double>& p);

    /// \brief Check for the same sign on segment ends.
    ///
    /// Check if function has the same sign on segment ends.
    ///
    /// \return
    /// true - if function has the same sign on segment ends,
    /// false - otherwise.
    inline bool
    is_same_sign_on_segment_ends() const
    {
        return (lo.second * hi.second > 0.0);
    }

    // Calculate next point.
    void
    calc_next_point(SegmentFunctionPullInType type,
                    pair<double, double>& p);

    // Move bounds based on point.
    double
    move_bounds(const pair<double, double>& p);
};

/// @}

}

}

#endif // !CAESAR_MTH_SEGMENT_FUNCTION_H
