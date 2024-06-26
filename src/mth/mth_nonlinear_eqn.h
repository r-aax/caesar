/// \file
/// \brief Declaration methods solving nonlinear equations.
///
/// List of available mathods:
/// - bisection method,
/// - chords method,
/// - combined method.

#ifndef MTH_NONLINEAR_EQN_H
#define MTH_NONLINEAR_EQN_H

#include "mth_segment_function.h"

namespace mth
{

/// \addtogroup mth
/// @{

/// \brief Nonlinear equation solver method.
enum class NonlinearEqnMethodType
{
    /// \brief Bisection method.
    Bisection,

    /// \brief Chords method.
    Chords,

    /// \brief Combined method.
    Combined,

    /// \brief Undefined.
    Undefined
};

/// \brief Result of nonlinear equation solver.
enum class NonlinearEqnStatus
{
    /// \brief Equation doesn't need to be solved.
    ///
    /// Old root already satisfies equation.
    YesOldRoot,

    /// \brief Equation is solved with new root.
    YesNewRoot,

    /// \brief We do not solve equation because of same sign on function on segment ends.
    NoBecauseSameSign,

    /// \brief Equation can not be solved because of function discountinuity.
    NoBecauseDiscontinuousFunction,

    /// \brief Equation is not solved because of number of iterations.
    NoBecauseOutOfIterations,

    /// \brief Undefined.
    Undefined
};

/// \brief Pointer to method for solving nonlinear equations.
typedef NonlinearEqnStatus (*NonlinearEqnMethod)(Function1D f,
                                                 void* data,
                                                 vector<double>& segm,
                                                 double& root);

/// @brief Class for solving nonlinear equations.
class NonlinearEqn
{

private:

    /// \brief Epsilon for argument (X).
    double x_eps { 0.0 };

    /// \brief Epsilon for function value (F(X)).
    double f_eps { 0.0 };

    /// \brief Maximum count of iterations.
    int max_iters_count { 0 };

    // Check solver is ready for using.
    bool
    is_ready() const;

    // Solve equation.
    NonlinearEqnStatus
    solve(Function1D f,
          void* data,
          const vector<double>& segm,
          NonlinearEqnMethodType method,
          double& root) const;

public:

    // Set global parameters.
    void
    set_global_parameters(double x_eps_,
                          double f_eps_,
                          int max_iters_count_);

    // Bisection method.
    NonlinearEqnStatus
    solve_bisection(Function1D f,
                    void* data,
                    const vector<double>& segm,
                    double& root) const;

    // Chords method.
    NonlinearEqnStatus
    solve_chords(Function1D f,
                 void* data,
                 const vector<double>& segm,
                 double& root) const;

    // Combined method.
    NonlinearEqnStatus
    solve_combined(Function1D f,
                   void* data,
                   const vector<double>& segm,
                   double& root) const;
};

/// @}

}

#endif // !MTH_NONLINEAR_EQN_H
