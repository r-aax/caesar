/// \file
/// \brief Node implementation.
///
/// Mesh node implementation.

#include "mesh_node.h"

#include "mesh_edge.h"
#include "mesh_cell.h"

namespace mesh
{

/// \addtogroup mesh
/// @{

#ifdef DEBUG
// Counter initialization.
int Node::counter = 0;
#endif // DEBUG

/// \brief Print function.
///
/// Print node to stream.
///
/// \param[in] os Output stream.
/// \param[in] n  Node.
///
/// \return
/// Output stream.
ostream&
operator<<(ostream& os,
           const Node& n)
{
    os << "node " << setw(5) << n.get_ids_string() << " :";

    // Print edges.
    size_t en = n.edges.size();
    os << " edges(";
    for (size_t i = 0; i < en; ++i)
    {
        os << n.edges[i]->get_id();

        if (i < en - 1)
        {
            os << ",";
        }
    }
    os << "),";

    // Print cells.
    size_t cn = n.cells.size();
    os << " cells(";
    for (size_t i = 0; i < cn; ++i)
    {
        os << n.cells[i]->get_id();

        if (i < cn - 1)
        {
            os << ",";
        }
    }
    os << ")";

    return os;
}

/// \brief Check if node is inner.
///
/// Check node is inner.
///
/// \return
/// true - if node is inner,
/// false - otherwise.
bool
Node::is_inner() const
{
    for (const auto e : edges)
    {
        if (!e->is_inner())
        {
            return false;
        }
    }

    return true;
}

//
// Geometry.
//

/// \brief Calculate outer normal.
void
Node::calc_outer_normal()
{
    normal.zero();

    for (auto cell : cells)
    {
        normal.add(cell->normal);
    }

    normal.div(static_cast<double>(cells.size()));
}

/// @}

}
