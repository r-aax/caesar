/// \file
/// \brief Node implementation.
///
/// Mesh node implementation.

#include "mesh_node.h"

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
int Node::counter = 0;
#endif // DEBUG

//
// Print.
//

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
    size_t en = n.edges_count();
    os << " edges(";
    for (size_t i = 0; i < en; ++i)
    {
        os << n.edge(i)->get_id();

        if (i < en - 1)
        {
            os << ",";
        }
    }
    os << "),";

    // Print cells.
    size_t cn = n.cells_count();
    os << " cells(";
    for (size_t i = 0; i < cn; ++i)
    {
        os << n.cell(i)->get_id();

        if (i < cn - 1)
        {
            os << ",";
        }
    }
    os << ")";

    return os;
}

//
// Simple properties.
//

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
    size_t ec { edges_count() };

    for (size_t i = 0; i < ec; ++i)
    {
        const Edge* e { edge(i) };

        if (!e->is_inner())
        {
            return false;
        }
    }

    return true;
}

//
// Work with geometry.
//

/// \brief Calculate outer normal.
void
Node::calc_normal()
{
    size_t cc { cells_count() };

    normal_.zero();

    for (size_t i = 0; i < cc; ++i)
    {
        Cell* c { cell(i) };

        normal_.add(c->normal());
    }

    normal_.div(static_cast<double>(cells_count()));
}

//
// Work with remesh data.
//

/// \brief Calculate ice shift.
///
/// Calculate ice shift as mean value of incident cells ice shifts.
void
Node::calc_ice_shift()
{
    size_t cc { cells_count() };
    double x { 0.0 };

    for (size_t i = 0; i < cc; ++i)
    {
        const Cell* c { cell(i) };

        x += c->ice_shift;
    }

    ice_shift = (x / static_cast<double>(cells_count()));
}

/// @}

}

}
