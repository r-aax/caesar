/// \file
/// \brief Empty solver node core implementation.
///
/// \brief Empty solver node core implementation.

#include "solver_empty_node_core.h"

namespace solver
{

/// \addtogroup solver
/// @{

/// \brief Default constructor.
NodeCore::NodeCore()
{
}

/// \brief Default destructor.
NodeCore::~NodeCore()
{
}

/// \brief Print function.
///
/// Print node cell to stream.
///
/// \param[in] os Output stream.
/// \param[in] a  Node core.
ostream&
operator<<(ostream& os,
           const NodeCore& v)
{
    os << "nc:";

    return os;
}

/// \brief Get data element.
///
/// Get element data.
///
/// \param[in] name Name of variable.
///
/// \return
/// Value of data element.
double
NodeCore::get_data_element(const string& name)
{
    return 0.0;
}

/// \brief Set data element.
///
/// Set data element.
///
/// \param[in] name  Name of variable.
/// \param[in] value Data element value.
void
NodeCore::set_data_element(const string& name,
                           double value)
{
}

/// @}

}
