/// \file
/// \brief Cubic graph reduce history.
///
/// Cubic graph reduce history for restore purposes.

#ifndef CAESAR_GRAPH_CUBIC_GRAPH_REDUCE_HISTORY_H
#define CAESAR_GRAPH_CUBIC_GRAPH_REDUCE_HISTORY_H

#include "utils/utils.h"
#include "graph_cubic_graph_reduce_history_step.h"

namespace caesar
{

namespace graph
{

/// \addtogroup graph
/// @{

/// \brief Cubic graph reduce history.
class CubicGraphReduceHistory
{

private:

    /// \brief History.
    vector<CubicGraphReduceHistoryStep> history;

public:

    // Default constructor.
    CubicGraphReduceHistory();

    // Default destructor.
    ~CubicGraphReduceHistory();

    // Remember.
    void
    remember(int v1_id,
             int v2_id,
             int e_id,
             int v1_e1_id,
             int v1_e2_id,
             int v2_e1_id,
             int v2_e2_id,
             int result_e1_id,
             int result_e2_id);

    //
    // Get last step data.
    //

    /// \brief Get first vertex id.
    ///
    /// Get first vertex id.
    ///
    /// \return
    /// First vertex id.
    inline int
    get_v1_id() const
    {
        return history.back().v1_id;
    }

    /// \brief Get second vertex id.
    ///
    /// Get second vertex id.
    ///
    /// \return
    /// Second vertex id.
    inline int
    get_v2_id() const
    {
        return history.back().v2_id;
    }

    /// \brief Get delete edge identifier.
    ///
    /// Get deleted edge identifier.
    ///
    /// \return
    /// Deleted edge identifier.
    inline int
    get_e_id() const
    {
        return history.back().e_id;
    }

    /// \brief Get first vertex first edge id.
    ///
    /// Get first vertex first edge id.
    ///
    /// \return
    /// First vertex first edge id.
    inline int
    get_v1_e1_id() const
    {
        return history.back().v1_e1_id;
    }

    /// \brief Get first vertex second edge id.
    ///
    /// Get first vertex second edge id.
    ///
    /// \return
    /// First vertex second edge id.
    inline int
    get_v1_e2_id() const
    {
        return history.back().v1_e2_id;
    }

    /// \brief Get second vertex first egde id.
    ///
    /// Get second vertex first edge id.
    ///
    /// \return
    /// Second vertex first edge id.
    inline int
    get_v2_e1_id() const
    {
        return history.back().v2_e1_id;
    }

    /// \brief Get second vertex second edge id.
    ///
    /// Get second vertex second edge id.
    ///
    /// \return
    /// Second vertex second edge id.
    inline int
    get_v2_e2_id() const
    {
        return history.back().v2_e2_id;
    }

    /// \brief Get first result edge id.
    ///
    /// Get first result edge id.
    ///
    /// \return
    /// First result edge id.
    inline int
    get_result_e1_id() const
    {
        return history.back().result_e1_id;
    }

    /// \brief Get second result edge id.
    ///
    /// Get second result edge id.
    ///
    /// \return
    /// Second reult id.
    inline int
    get_result_e2_id() const
    {
        return history.back().result_e2_id;
    }

    /// \brief Get last record.
    ///
    /// Get last step of history.
    ///
    /// \return
    /// Last step of history.
    inline const CubicGraphReduceHistoryStep&
    get() const
    {
        return history.back();
    }

    //
    // Check and remove last step.
    //

    /// \brief Check for emptyness.
    ///
    /// Check for emptyness.
    ///
    /// \return
    /// true - if history is empty,
    /// false - otherwise.
    inline bool
    is_empty() const
    {
        return history.empty();
    }

    /// \brief Remove last step.
    ///
    /// Remove last step.
    inline void
    pop()
    {
        history.pop_back();
    }
};

/// @}

}

}

#endif // !CAESAR_GRAPH_CUBIC_GRAPH_REDUCE_HISTORY_H
