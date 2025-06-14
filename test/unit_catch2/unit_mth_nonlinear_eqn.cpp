/// \file
/// \brief Tests for nonlinear equations solver.
///
/// Tests for nonlinear equations solver.

#include <catch2/catch_test_macros.hpp>
#include "caesar.h"

using namespace caesar;

/// \brief Linear function.
///
/// Linear function:
///
/// @f$ y = x @f$
///
/// \param[in] x    Argument.
/// \param[in] data Additional data.
///
/// \return
/// Function value.
double function_linear(double x,
                       void* data)
{
    (void)data;

    return x;
}

/// \brief Cubic function.
///
/// Cubic function:
///
/// @f$ y = x^3 - 2 x^2 - 100 x + 200 @f$
///
/// \param[in] x    Argument.
/// \param[in] data Additional data.
///
/// \return
/// Function value.
double function_cubic(double x,
                      void* data)
{
    (void)data;

    return (x * x * x) - (2.0 * x * x) - (100.0 * x) + 200.0;
}

TEST_CASE("NonlinearEqn : nonlinear equation solver", "[mth]")
{
    SECTION("linear function")
    {
        double add { 0.0 }, root { 0.0 }, value_out_of_segm { -1000.0 };
        mth::Segment segment(-100.0, 100.0);
        double right { 0.0 };
        double f_eps { 1.0e-6 };
        mth::NonlinearEqnStatus st { mth::NonlinearEqnStatus::Undefined };
        mth::NonlinearEqn solver;

        solver.set_global_parameters(1.0e-6, f_eps, 100);

        // bisection
        root = value_out_of_segm;
        st = solver.solve_bisection(function_linear,
                                    static_cast<void*>(&add),
                                    segment,
                                    root);
        CHECK(st == mth::NonlinearEqnStatus::YesNewRoot);
        CHECK(mth::is_near(root, right, f_eps));

        // chords
        root = value_out_of_segm;
        st = solver.solve_chords(function_linear,
                                 static_cast<void*>(&add),
                                 segment,
                                 root);
        CHECK(st == mth::NonlinearEqnStatus::YesNewRoot);
        CHECK(mth::is_near(root, right, f_eps));

        // combined
        root = value_out_of_segm;
        st = solver.solve_combined(function_linear,
                                   static_cast<void*>(&add),
                                   segment,
                                   root);
        CHECK(st == mth::NonlinearEqnStatus::YesNewRoot);
        CHECK(mth::is_near(root, right, f_eps));

        // wrong interval
        root = 0.0;
        st = solver.solve_combined(function_linear,
                                   static_cast<void*>(&add),
                                   mth::Segment(0.0, -1.0),
                                   root);
        CHECK(st == mth::NonlinearEqnStatus::NoBecauseWrongSegment);
    }

    SECTION("cubic function")
    {
        double add { 0.0 }, root { 0.0 }, value_out_of_segm { -1000.0 };
        mth::Segment segment(-5.0, 5.0);
        double right { 2.0 };
        double f_eps { 1.0e-6 };
        mth::NonlinearEqnStatus st { mth::NonlinearEqnStatus::Undefined };
        mth::NonlinearEqn solver;

        solver.set_global_parameters(1.0e-6, f_eps, 100);

        root = value_out_of_segm;
        st = solver.solve_bisection(function_cubic,
                                    static_cast<void*>(&add),
                                    segment,
                                    root);
        CHECK(st == mth::NonlinearEqnStatus::YesNewRoot);
        CHECK(mth::is_near(root, right, f_eps));

        root = value_out_of_segm;
        st = solver.solve_chords(function_cubic,
                                 static_cast<void*>(&add),
                                 segment,
                                 root);
        CHECK(st == mth::NonlinearEqnStatus::YesNewRoot);
        CHECK(mth::is_near(root, right, f_eps));

        root = value_out_of_segm;
        st = solver.solve_combined(function_cubic,
                                   static_cast<void*>(&add),
                                   segment,
                                   root);
        CHECK(st == mth::NonlinearEqnStatus::YesNewRoot);
        CHECK(mth::is_near(root, right, f_eps));
    }
}
