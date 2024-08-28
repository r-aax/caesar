/// \file
/// \brief Cubic graph reduce history implementation.
///
/// Cubic graph reduce history implementation.

#include "graph_cubic_graph_reduce_history.h"

namespace caesar
{

namespace graph
{

/// \addtogroup graph
/// @{

/// \brief Default constructor.
///
/// Default constructor.
CubicGraphReduceHistory::CubicGraphReduceHistory()
{
}

/// \brief Default destructor.
///
/// Deafult destructor.
CubicGraphReduceHistory::~CubicGraphReduceHistory()
{
}

/// \brief Remember.
///
/// Remember one step of history.
///
/// \param[in] v1_id        First vertex id.
/// \param[in] v2_id        Second vertex id.
/// \param[in] e_id          Deleted edge id.
/// \param[in] v1_e1_id     First vertex first edge id.
/// \param[in] v1_e2_id     First vertex second edge id.
/// \param[in] v2_e1_id     Second vertex first edge id.
/// \param[in] v2_e2_id     Second vertex second edge id.
/// \param[in] result_e1_id First result edge id.
/// \param[in] result_e2_id Second result edge id.
void
CubicGraphReduceHistory::remember(int v1_id,
                                  int v2_id,
                                  int e_id,
                                  int v1_e1_id,
                                  int v1_e2_id,
                                  int v2_e1_id,
                                  int v2_e2_id,
                                  int result_e1_id,
                                  int result_e2_id)
{
    history.push_back(CubicGraphReduceHistoryStep(v1_id, v2_id, e_id,
                                                  v1_e1_id, v1_e2_id, v2_e1_id, v2_e2_id,
                                                  result_e1_id, result_e2_id));
}

/// @}

}

}
