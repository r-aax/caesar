/// \file
/// \brief Implementation of function defined on segment.
///
/// Function defined on segment.

#include "mth_segment_function.h"

namespace caesar
{

namespace mth
{

/// \addtogroup mth
/// @{

/// \brief Calculate bisection next point.
///
/// Calculate bisection next point.
/// We take just mid point and function value in it.
///
/// \param[out] p Point.
void
SegmentFunction::calc_bisection_next_point(pair<double, double>& p)
{
    p.first = 0.5 * (lo.first + hi.first);
    p.second = f(p.first, data);
}

/// \brief Calculate next point for chords method.
///
/// Calculate next point for chords method.
///
/// \param[out] p Point.
void
SegmentFunction::calc_chords_next_point(pair<double, double>& p)
{
    double ky = -lo.second / hi.second;

    p.first = (ky * hi.first + lo.first) / (ky + 1.0);
    p.second = f(p.first, data);
}

/// \brief Default constructor.
///
/// Default constructor.
///
/// \param[in] f_      Function.
/// \param[in] data_   Additional data.
/// \param[in] segment Segment.
SegmentFunction::SegmentFunction(Function1D f_,
                                 void* data_,
                                 Segment segment)
    : f(f_),
      data(data_)
{
    // Init low and high bounds with segment bounds.
    // But now we do not init function values because
    // calculating values of function may be expensive operation.
    lo.first = segment.lo();
    hi.first = segment.hi();
}

/// \brief Default destructor.
///
/// Default destructor.
SegmentFunction::~SegmentFunction()
{
}

/// \brief Init function values on segment ends.
///
/// Init function values on segment ends.
void
SegmentFunction::init_segment_ends_function_values()
{
    lo.second = f(lo.first, data);
    hi.second = f(hi.first, data);
}

/// \brief Init segment ends by from inner point.
///
/// Init segment ends from inner point.
///
/// \param[in] p Point.
void
SegmentFunction::init_segment_ends_from_inner_point(const pair<double, double>& p)
{
    // Calculate low function value.
    double flo = f(lo.first, data);

    if (flo * p.second > 0.0)
    {
        // Low bound and p are the same sign,
        // so we have to modify segment to [p, high].
        lo.first = p.first;
        lo.second = p.second;
        hi.second = f(hi.first, data);
    }
    else
    {
        // Low bound and p are different signs,
        // so we have to set segment to [low, p].
        lo.second = flo;
        hi.first = p.first;
        hi.second = p.second;
    }
}

/// \brief Calculate next point.
///
/// Calculate next point for pull in segment.
///
/// \param[in]  type Type of pull in.
/// \param[out] p    Point.
void
SegmentFunction::calc_next_point(SegmentFunctionPullInType type,
                                 pair<double, double>& p)
{
    switch (type)
    {
        case SegmentFunctionPullInType::Bisection:
            calc_bisection_next_point(p);
            break;

        case SegmentFunctionPullInType::Chords:
            calc_chords_next_point(p);
            break;

        default:
            DEBUG_ERROR("undefined type of segment function pull in");
    }
}

/// \brief Move bounds based on point.
///
/// Move low or high bound to point.
///
/// \param[in] p Point.
///
/// \return
/// Reduce segment ratio.
double
SegmentFunction::move_bounds(const pair<double, double>& p)
{
    double old_length = segment_length();
    double new_length { 0.0 };

    if (p.second * lo.second > 0.0)
    {
        // Low bound moving up.
        lo.first = p.first;
        lo.second = p.second;
    }
    else
    {
        // High bound moving down.
        hi.first = p.first;
        hi.second = p.second;
    }

    new_length = segment_length();

    return new_length / old_length;
}

/// @}

}

}
