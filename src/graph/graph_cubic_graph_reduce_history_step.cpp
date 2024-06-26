/// \file
/// \brief Cubic graph reduce history step implementation.
///
/// Cubic graph reduce history step implementation.

#include "graph_cubic_graph_reduce_history_step.h"

namespace graph
{

/// \addtogroup graph
/// @{

/// \brief Default constructor.
///
/// Default constructor by all values.
///
/// \param[in] v1_id_        First vertex id.
/// \param[in] v2_id_        Second vertex id.
/// \param[in] e_id_         Deleted edge id.
/// \param[in] v1_e1_id_     First vertex first edge id.
/// \param[in] v1_e2_id_     First vertex second edge id.
/// \param[in] v2_e1_id_     Second vertex first edge id.
/// \param[in] v2_e2_id_     Second vertex second edge id.
/// \param[in] result_e1_id_ First result edge id.
/// \param[in] result_e2_id_ Second result edge id.
CubicGraphReduceHistoryStep::CubicGraphReduceHistoryStep(int v1_id_,
                                                         int v2_id_,
                                                         int e_id_,
                                                         int v1_e1_id_,
                                                         int v1_e2_id_,
                                                         int v2_e1_id_,
                                                         int v2_e2_id_,
                                                         int result_e1_id_,
                                                         int result_e2_id_)
    : v1_id { v1_id_ },
      v2_id { v2_id_ },
      e_id { e_id_ },
      v1_e1_id { v1_e1_id_ },
      v1_e2_id { v1_e2_id_ },
      v2_e1_id { v2_e1_id_ },
      v2_e2_id { v2_e2_id_ },
      result_e1_id { result_e1_id_ },
      result_e2_id { result_e2_id_ }
{
}

/// \brief Default destructor.
///
/// Default destructor.
CubicGraphReduceHistoryStep::~CubicGraphReduceHistoryStep()
{
}

/// \brief Print function.
///
/// Print function.
///
/// \param[in,out] os Out stream.
/// \param[in]     x  Structure to print.
///
/// \return
/// Out stream.
ostream&
operator<<(ostream& os,
           const CubicGraphReduceHistoryStep& x)
{
    os << "e" << x.e_id
       << " [(v"
       << x.v1_id << " : e" << x.v1_e1_id << ", e" << x.v1_e2_id << " -> re" << x.result_e1_id
       << "), (v"
       << x.v2_id << " : e" << x.v2_e1_id << ", e" << x.v2_e2_id << " -> re" << x.result_e2_id
       << ")]";

    return os;
}

/// @}

}
