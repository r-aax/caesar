/// \file
/// \brief Implementation of bicolor cycle.
///
/// Implementation of bicolor cycle.
///
///          c1        c2                c1
///        *====*---------------*================*
///     c2 |                                     | c2
///        |                                     |
///        *===========*------------*============*
///             c1           c2            c1

#include "graph_bicolor_cycle.h"
#include "mth/mth.h"

namespace caesar
{

namespace graph
{

/// \addtogroup graph
/// @{

/// \brief Default constructor.
///
/// Default constructor.
BicolorCycle::BicolorCycle()
{
}

/// \brief Default destructor.
///
/// Default destructor.
BicolorCycle::~BicolorCycle()
{
}

/// \brief Print function.
///
/// Print function.
///
/// \param[in,out] os Out stream.
/// \param[in]     bc Bicolor cycle.
ostream&
operator<<(ostream& os,
           const BicolorCycle& bc)
{
    size_t ec { bc.edges.size() };

    cout << "BicolorCycle :";

    for (size_t i = 0; i < ec; ++i)
    {
        Edge* e { bc.edges[i] };

        cout << " [" << (*e) << "]";
    }

    cout << endl;

    return os;
}

//
// Build cycle.
//

/// \brief Build cycle.
///
/// Build cycle from start edge and another color.
///
///
void
BicolorCycle::build(Edge* start_edge,
                    int another_color)
{
    // Clear old cycle.
    edges.clear();
    ids.clear();

    DEBUG_CHECK_ERROR(start_edge->get_color() != another_color, "bicolor cycle requires two diffirent colors");

    // Sum colors for calculating next color.
    int sum_colors { start_edge->get_color() + another_color };

    // Start with start edge.
    edges.push_back(start_edge);
    ids.insert(start_edge->get_id());

    // We can walk edges in any order.
    // Fix a vertex and go to b vertex.
    Vertex* start_vertex { start_edge->get_a() };
    Vertex* next_vertex { start_edge->get_b() };

    // Next color is another color.
    int next_color { another_color };

    // Traverse the cycle.
    while (next_vertex != start_vertex)
    {
        for (Edge* next_edge : next_vertex->get_edges())
        {
            if (next_edge->get_color() == next_color)
            {
                edges.push_back(next_edge);
                ids.insert(next_edge->get_id());
                next_vertex = next_vertex->neighbour(next_edge);
                next_color = sum_colors - next_color;

                break;
            }
        }
    }

    DEBUG_CHECK_ERROR(mth::is_even(len()), "bicolor cycle length must be even");
}

/// \brief Switch colors.
///
/// Switch colors.
/// Replace first color with second color and vice versa.
void
BicolorCycle::switch_colors()
{
    size_t ec { edges.size() };
    int sum_colors { edges[0]->get_color() + edges[1]->get_color() };

    for (size_t i = 0; i < ec; ++i)
    {
        Edge* e { edges[i] };

        e->set_color(sum_colors - e->get_color());
    }
}

/// \brief Switch colors between two edges.
///
/// Switch colors between two edges.
///
/// \param[in] e1 First edge.
/// \param[in] e2 Second edge.
void
BicolorCycle::switch_colors(const Edge* e1,
                            const Edge* e2)
{
    size_t ec { edges.size() };
    int sum_colors { edges[0]->get_color() + edges[1]->get_color() };
    bool is_need_to_switch { false };

    for (size_t i = 0; i < ec; ++i)
    {
        Edge* e { edges[i] };

        if (is_need_to_switch)
        {
            if ((e == e1) || (e == e2))
            {
                // No more swithes.
                return;
            }
            else
            {
                e->set_color(sum_colors - e->get_color());
            }
        }
        else
        {
            if ((e == e1) || (e == e2))
            {
                is_need_to_switch = true;
            }
        }
    }
}

/// @}

}

}
