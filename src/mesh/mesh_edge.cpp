/// \file
/// \brief Edge implementation.
///
/// Mesh edge implementation.

#include "mesh_edge.h"

#include "mesh_cell.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

#ifdef DEBUG
// Counter initialization.
int Edge::counter = 0;
#endif // DEBUG

/// \brief Print function.
///
/// Print edge to stream.
///
/// \param[in] os Output stream.
/// \param[in] e  Edge.
ostream&
operator<<(ostream& os,
           const Edge& e)
{
    os << "edge " << setw(5) << e.get_ids_string() << " :";

    // Print nodes.
    size_t nn = e.nodes.size();
    os << " nodes(";
    for (size_t i = 0; i < nn; ++i)
    {
        os << e.nodes[i]->get_id();

        if (i < nn - 1)
        {
            os << "-";
        }
    }
    os << "),";

    // Print cells.
    size_t cn = e.cells.size();
    os << " cells(";
    for (size_t i = 0; i < cn; ++i)
    {
        os << e.cells[i]->get_id();

        if (i < cn - 1)
        {
            os << ",";
        }
    }
    os << "),";

    // Print other data.
    os << " length = " << e.length << " m";

    return os;
}

//
// Some edge flags.
//

/// \brief Check if edge is cross-domain.
///
/// Check if edge is cross-domain.
///
/// \return
/// true - if edge is cross-domain,
/// false - otherwise.
bool
Edge::is_cross() const
{
    return is_inner() && (cells[0]->domain != cells[1]->domain);
}

/// \brief Cell 0.
///
/// Get cell 0.
///
/// \return
/// Cell 0.
Cell*
Edge::cell_0()
{
    return cells[0];
}

/// \brief Cell 1.
///
/// Get cell 1.
///
/// \return
/// Cell 1.
Cell*
Edge::cell_1()
{
    return cells[1];
}

/// \brief Domain of cell 0.
///
/// Get domain of cell 0.
///
/// \return
/// Domain of cell 0.
size_t
Edge::domain_0()
{
    Cell* c = cell_0();

    DEBUG_CHECK_ERROR(c != nullptr, "edge has no 0-th cell");

    return c->domain;
}

/// \brief Domain of cell 1.
///
/// Get domain of cell 1.
///
/// \return
/// Domain of cell 1.
size_t
Edge::domain_1()
{
    Cell* c = cell_1();

    DEBUG_CHECK_ERROR(c != nullptr, "edge has no 1-st cell");

    return c->domain;
}

//
// Geometry.
//

/// \brief Calculate length.
///
/// Calculate length - distance betweeen two points.
void
Edge::calc_length()
{
    length = nodes[0]->get_point().dist_to(nodes[1]->get_point());
}

/// @}

}

}
