/// \file
/// \brief Cell implementation.
///
/// Mesh cell implementation.

#include "mesh_cell.h"

#include <set>

#include "mesh_zone.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

#ifdef DEBUG
// Counter initialization.
int Cell::counter = 0;
#endif // DEBUG

/// \brief Print function.
///
/// Print cell to stream.
///
/// \param[in] os Output stream.
/// \param[in] c  Cell.
ostream&
operator<<(ostream& os,
           const Cell& c)
{
    static const string tab(12, ' ');

    os << "cell " << setw(5) << c.get_ids_string() << " :";

    // Domain number.
    os << " d" << c.domain;

    // Print nodes.
    size_t nn = c.nodes_count();
    os << ", nodes(";
    for (size_t i = 0; i < nn; ++i)
    {
        os << c.node(i)->get_id();

        if (i < nn - 1)
        {
            os << "-";
        }
    }
    os << "),";

    // Print edges.
    size_t en = c.edges_count();
    os << " edges(";
    for (size_t i = 0; i < en; ++i)
    {
        os << c.edge(i)->get_id();

        if (i < en - 1)
        {
            os << ",";
        }
    }
    os << ")";

    // Geometry data.
    os << endl << tab;
    os << " Area = " << c.area << " m^2";
    os << ", center = " << c.center;
    os << endl << tab;
    os << " fictitious_points = "
       << c.fictitious_points[0] << ", "
       << c.fictitious_points[1] << ", "
       << c.fictitious_points[2];
    os << endl << tab;
    os << " normal = " << c.normal;
    os << " fictitious_normal = " << c.fictitious_normal;

    return os;
}

//
// Links manipulation.
//

/// \brief Get neighbour through the edge.
///
/// Get neighbour through the edge.
///
/// \param[in] e Edge.
///
/// Neighbour face.
Cell*
Cell::get_neighbour(Edge* e)
{
    DEBUG_CHECK_ERROR(e->cells_count() == 2, "unable to take cell neighbour for border edge");

    if (e->cell(0) == this)
    {
        return e->cell(1);
    }
    else
    {
        return e->cell(0);
    }
}

/// \brief Fill list of neighbours by nodes.
///
/// Fill vector with all neighbours by all nodes.
///
/// \param[out] ngh Vector of neighbours.
void
Cell::get_neighbours_by_nodes(vector<Cell*>& ngh)
{
    set<int> ids;

    ngh.clear();

    for (auto n : nodes())
    {
        for (auto c : n->cells())
        {
            if (c != this)
            {
                int id = c->get_id();

                if (ids.find(id) == ids.end())
                {
                    ngh.push_back(c);
                    ids.insert(id);
                }
            }
        }
    }
}

/// \brief Init fictitious points.
///
/// Copy node points to fictitious points.
void
Cell::init_fictitious_points()
{
    for (auto node : nodes())
    {
        fictitious_points.push_back(geom::Vector(node->point()));
    }
}

/// \brief Init neighbourhood.
void
Cell::init_neighbourhood()
{
    get_neighbours_by_nodes(neighbourhood);
}

//
// Geometry.
//

/// \brief Calculata area.
void
Cell::calc_area()
{
    area = geom::Vector::triangle_area(node(0)->point(),
                                       node(1)->point(),
                                       node(2)->point());
}

/// \brief Calculate center vector.
void
Cell::calc_center()
{
    center.zero();

    for (auto n : nodes())
    {
        center.add(n->point());
    }

    center.div(static_cast<double>(nodes_count()));
}

/// \brief Calculate outer normal.
///
/// Calculate real outer normal.
void
Cell::calc_outer_normal()
{
    geom::Vector::calc_outer_normal(node(0)->point(), node(1)->point(), node(2)->point(), normal);
}

/// \brief Calculate fictitious outer normal.
///
/// Calculate fictitious outer normal.
void
Cell::calc_fictitious_outer_normal()
{
    geom::Vector::calc_outer_normal(fictitious_points[0], fictitious_points[1], fictitious_points[2],
                                    fictitious_normal);
}

/// @}

}

}
