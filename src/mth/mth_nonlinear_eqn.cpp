/// \file
/// \brief Implementation of solving nonlinear equations.
///
/// Implementation of solving nonlinear equations.

#include "mth_nonlinear_eqn.h"
#include "mth_basics.h"

namespace mth
{

/// \addtogroup mth
/// @{

/// \brief Check solver is ready for using.
///
/// Check solver is ready for use.
///
/// \return
/// true - if solver is ready,
/// false - otherwise.
bool
NonlinearEqn::is_ready() const
{
    return (x_eps > 0.0) && (f_eps > 0.0) && (max_iters_count > 0);
}

/// \brief Set global parameters.
///
/// Set global parameters.
///
/// \param[in] x_eps_           Epsilon for X.
/// \param[in] f_eps_           Epsilon for F(X).
/// \param[in] max_iters_count_ Maximum number of iterations.
void
NonlinearEqn::set_global_parameters(double x_eps_,
                                    double f_eps_,
                                    int max_iters_count_)
{
    x_eps = x_eps_;
    f_eps = f_eps_;
    max_iters_count = max_iters_count_;
}

/// Solve equation.
///
/// Solve equation with direct method (pull in methods family).
///
/// \param[in]  f      Function.
/// \param[in]  data   Additional parameter.
/// \param[in]  segm   Segment for searching the root.
/// \param[in]  method Method.
/// \param[out] root   Equation root.
///
/// \return
/// Status of solving equation.
NonlinearEqnStatus
NonlinearEqn::solve(Function1D f,
                    void* data,
                    const vector<double>& segm,
                    NonlinearEqnMethodType method,
                    double& root) const
{
    // Debug checkers.
    DEBUG_CHECK_ERROR(is_ready(), "solver is not ready for using");
    DEBUG_CHECK_ERROR(segm[0] <= segm[1], "wrong interval for solving nonlinear equation");

    SegmentFunction sf(f, data, segm);
    SegmentFunctionPullInType pull_in_type { SegmentFunctionPullInType::Undefined };
    pair<double, double> p;

    // Define start pull in type for method.
    switch (method)
    {
        case NonlinearEqnMethodType::Bisection:
            pull_in_type = SegmentFunctionPullInType::Bisection;
            break;

        case NonlinearEqnMethodType::Chords:
        case NonlinearEqnMethodType::Combined:
            pull_in_type = SegmentFunctionPullInType::Chords;
            break;

        default:
            DEBUG_ERROR("unknown nonlinear equation solving method");
    }

    // Maybe our given root already satisfies conditions.
    if (sf.is_arg_on_segment(root))
    {
        p.first = root;
        p.second = f(p.first, data);

        if (is_near(p.second, 0.0, f_eps))
        {
            return NonlinearEqnStatus::YesOldRoot;
        }

        sf.init_segment_ends_from_inner_point(p);
    }
    else
    {
        sf.init_segment_ends_function_values();
    }

    // We solve equation only for functions which have values of different signs on interval ends.
    if (sf.is_same_sign_on_segment_ends())
    {
        return NonlinearEqnStatus::NoBecauseSameSign;
    }

    // Find root with iterations.
    for (int i = 0; i < max_iters_count; ++i)
    {
        sf.calc_next_point(pull_in_type, p);

        if (is_near(p.second, 0.0, f_eps))
        {
            root = p.first;

            return NonlinearEqnStatus::YesNewRoot;
        }

        double k = sf.move_bounds(p);

        // Next iteration pull in type selection.
        switch (method)
        {
            case NonlinearEqnMethodType::Bisection:
            case NonlinearEqnMethodType::Chords:

                // Nothing changes.
                break;

            case NonlinearEqnMethodType::Combined:

                // issue #97
                // If segment is pulling in too slow we change pull in type into bisection.
                // Otherwise we use chords.
                pull_in_type = (k < 1.0 - k)
                               ? SegmentFunctionPullInType::Chords
                               : SegmentFunctionPullInType::Bisection;

                break;

            default:
                DEBUG_ERROR("unknown nonlinear equation solving method");
        }
    }

    return NonlinearEqnStatus::NoBecauseOutOfIterations;
}

/// \brief Solving with bisection method.
///
/// \param[in]  f    Function.
/// \param[in]  data Additional parameter.
/// \param[in]  segm Segment for searching the root.
/// \param[out] root Equation root.
///
/// \return
/// Status of solving equation.
NonlinearEqnStatus
NonlinearEqn::solve_bisection(Function1D f,
                              void* data,
                              const vector<double>& segm,
                              double& root) const
{
    return solve(f, data, segm, NonlinearEqnMethodType::Bisection, root);
}

/// \brief Chords method.
///
/// \param[in]  f    Function.
/// \param[in]  data Additional parameter.
/// \param[in]  segm Segment for searching the root.
/// \param[out] root Equation root.
///
/// \return
/// Status of solving equation.
NonlinearEqnStatus
NonlinearEqn::solve_chords(Function1D f,
                           void* data,
                           const vector<double>& segm,
                           double& root) const
{
    return solve(f, data, segm, NonlinearEqnMethodType::Chords, root);
}

/// \brief Combined method.
///
/// Combined method which includes bisection and chords iterations.
///
/// \param[in]  f    Function.
/// \param[in]  data Additional parameter.
/// \param[in]  segm Segment for searching the root.
/// \param[out] root Equation root.
///
/// \return
/// Status of solving equation.
NonlinearEqnStatus
NonlinearEqn::solve_combined(Function1D f,
                             void* data,
                             const vector<double>& segm,
                             double& root) const
{
    return solve(f, data, segm, NonlinearEqnMethodType::Combined, root);
}

/// @}

}
