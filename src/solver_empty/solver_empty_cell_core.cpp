/// \file
/// \brief Empty solver cell core implementation.
///
/// \brief Empty solver cell core implementation.

#include "solver_empty_cell_core.h"

namespace solver
{

/// \addtogroup solver
/// @{

/// \brief Default constructor.
CellCore::CellCore()
{
}

/// \brief Default destructor.
CellCore::~CellCore()
{
}

/// \brief Print function.
///
/// Print cell cell to stream.
///
/// \param[in] os Output stream.
/// \param[in] a  Cell core.
ostream&
operator<<(ostream& os,
           const CellCore& v)
{
    os << "cc: htc=" << v.htc << ", beta=" << v.beta;

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
CellCore::get_data_element(const string& name)
{
    if (name == "T")
    {
        return t;
    }
    else if (name == "Hw")
    {
        return hw;
    }
    else if (name == "Hi")
    {
        return hi;
    }
    else if (name == "HTC")
    {
        return htc;
    }
    else if (name == "Beta")
    {
        return beta;
    }
    else if (name == "TauX")
    {
        return tau_x;
    }
    else if (name == "TauY")
    {
        return tau_y;
    }
    else if (name == "TauZ")
    {
        return tau_z;
    }
    else
    {
        // Data element is ignored.
        return 0.0;
    }
}

/// \brief Set data element.
///
/// Set data element.
///
/// \param[in] name  Name of variable.
/// \param[in] value Data element value.
void
CellCore::set_data_element(const string& name,
                           double value)
{
    if (name == "T")
    {
        t = value;
    }
    else if (name == "Hw")
    {
        hw = value;
    }
    else if (name == "Hi")
    {
        hi == value;
    }
    else if (name == "HTC")
    {
        htc = value;
    }
    else if (name == "Beta")
    {
        beta = value;
    }
    else if (name == "TauX")
    {
        tau_x = value;
    }
    else if (name == "TauY")
    {
        tau_y = value;
    }
    else if (name == "TauZ")
    {
        tau_z = value;
    }
    else
    {
        // Data element is ignored.
    }
}

/// @}

}
