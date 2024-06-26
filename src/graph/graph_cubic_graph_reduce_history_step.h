/// \file
/// \brief Cubic graph reduce history step.
///
/// Cubic graph reduce history step.

#ifndef CUBIC_GRAPH_REDUCE_HISTORY_STEP_H
#define CUBIC_GRAPH_REDUCE_HISTORY_STEP_H

#include "utils/utils.h"

namespace graph
{

/// \addtogroup graph
/// @{

/// \brief Cubic graph reduce history step.
///
/// Cubic graph reduce history step.
class CubicGraphReduceHistoryStep
{
    friend class CubicGraphReduceHistory;

private:

    /// \brief First vertex id.
    int v1_id { -1 };

    /// \brief Second vertex id.
    int v2_id { -1 };

    /// \brief Deleted edge identifier.
    int e_id { -1 };

    /// \brief First vertex first edge id.
    int v1_e1_id { -1 };

    /// brief First vertex second edge id.
    int v1_e2_id { -1 };

    /// \brief Second vertex first edge id.
    int v2_e1_id { -1 };

    /// \brief Second vertex second edge id.
    int v2_e2_id { -1 };

    /// \brief First result edge id.
    int result_e1_id { -1 };

    /// \brief Second result edge id.
    int result_e2_id { -1 };

public:

    // Default constructor.
    CubicGraphReduceHistoryStep(int v1_id_,
                                int v2_id_,
                                int e_id_,
                                int v1_e1_id_,
                                int v1_e2_id_,
                                int v2_e1_id_,
                                int v2_e2_id_,
                                int result_e1_id_,
                                int result_e2_id_);

    // Default destructor.
    ~CubicGraphReduceHistoryStep();

    // Print function.
    friend ostream&
    operator<<(ostream& os,
               const CubicGraphReduceHistoryStep& x);

    /// \brief Is step refers to reduce by parallel edge.
    ///
    /// Check if step refers to reduce by parallel edge.
    ///
    /// \return
    /// true - if step refers to reduce by parallel edge,
    /// false - otherwise.
    inline bool
    is_reduce_by_parallel_edge() const
    {
        return result_e1_id == result_e2_id;
    }

    /// \brief Is step refers to reduce by unique edge.
    ///
    /// Check if step refers to reduce by unique edge.
    ///
    /// \return
    /// true - if step refers to reduce by unique edge,
    /// false - otherwise.
    inline bool
    is_reduce_by_unique_edge() const
    {
        return !is_reduce_by_parallel_edge();
    }
};

/// @}

}

#endif // !CUBIC_GRAPH_REDUCE_HISTORY_STEP_H
