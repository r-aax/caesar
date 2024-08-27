/// \file
/// \brief Graph edge implementation.
///
/// Graph edge implementation.

#include "graph_edge.h"

#include "mth/mth.h"

namespace graph
{

/// \addtogroup graph
/// @{

#ifdef DEBUG
// Counter initialization.
int Edge::counter = 0;
#endif // DEBUG

/// \brief Constructor with id.
///
/// Only graph can create the edge.
///
/// \param[in] id_ Identifier.
Edge::Edge(int id_)
    : id { id_ }
{

#ifdef DEBUG
   ++counter;
#endif // DEBUG

}

/// \brief Default destructor.
///
/// Default destructor.
Edge::~Edge()
{

#ifdef DEBUG
    --counter;
#endif // DEBUG

}

/// \brief Print function.
///
/// Print edge information.
///
/// \param[in,out] os Output stream.
/// \param[in]     e  Edge.
///
/// \return
/// Output stream.
ostream&
operator<<(ostream& os,
           const Edge& e)
{
    os << "e" << e.id << " : ("
       << e.get_end(0)->get_id() << "-" << e.get_end(1)->get_id()
       << "), color = " << e.get_color();

    return os;
}

//
// Arrange.
//

/// \brief Arrange vertices.
///
/// Arrange vertices in identifiers increasing order.
void
Edge::arrange_vertices_increasing_ids()
{
    sort(vertices.begin(), vertices.end(),
         [] (const Vertex* v1, const Vertex* v2)
         {
            return v1->get_id() < v2->get_id();
         });
}

//
// Relations other elements.
//

/// \brief Check if edge is incident to vertex.
///
/// Check if edge is incident to vertex.
///
/// \param[in] v Vertex.
///
/// \return
/// true - if edge is incident to vertex,
/// false - otherwise.
bool
Edge::is_incident(const Vertex* v) const
{
    for (auto x : vertices)
    {
        if (x == v)
        {
            return true;
        }
    }

    return false;
}

/// \brief Get end of the edge.
///
/// Get end of the edge.
///
/// \param[in] i Number of the end.
///
/// \return
/// End of the edge.
Vertex*
Edge::get_end(size_t i) const
{
    DEBUG_CHECK_ERROR(i < const_vertices_count, "wrong number of the end (" + to_string(i) + ")");

    return vertices[i];
}

//
// Reduce cubic graph.
//

/// \brief Check if edge is unique reduceable edge in cubic graph.
///
/// Check if edge is unique reduceable in cubic graph.
/// Edge in cubic graph is unique reduceable if:
/// - its ends' degrees are 3,
/// - both ends has 3 distinct neighbours.
///
///     C -----*            *----- E
///            |            |
///            A ---------- B
///            |            |
///     D -----*            *----- F
///
/// \return
/// true - if edge is unique and reduceable in cubic graph,
/// false - otherwise.
bool
Edge::is_cubic_graph_unique_reduceable_edge()
{
    Vertex* a { get_a() };
    Vertex* b { get_b() };

    // Check degrees.
    if ((a->degree() != 3) || (b->degree() != 3))
    {
        return false;
    }

    // Check distinct neighbours.
    if (a->has_parallel_edges() || b->has_parallel_edges())
    {
        return false;
    }

    return true;
}

/// \brief Check if edge is parallel reduceable edge in cubic graph.
///
/// Check if edge is parallel reduceable edge in cubic graph.
/// Edge in cubic graph is parallel reduceable if:
/// - its ends' degree are 3,
/// - edge is parallel,
/// - neighbours of a and b differ.
///
///             *----------*
///             |          |
///     C ----- A          B ----- D
///             |          |
///             *----------*
///
/// \return
/// true - if edge is parallel reduceable edge in cubic graph,
/// false - otherwise.
bool
Edge::is_cubic_graph_parallel_reduceable_edge()
{
    Vertex* a { get_a() };
    Vertex* b { get_b() };
    Vertex* c { nullptr };
    Vertex* d { nullptr };
    int a_cnt { 0 }, b_cnt { 0 };

    // Check degrees.
    if ((a->degree() != 3) || (b->degree() != 3))
    {
        return false;
    }

    // Calculate number of neighbours of a equal to b and set c vertex.
    for (auto e : a->get_edges())
    {
        Vertex* neigh { a->neighbour(e) };

        if (neigh == b)
        {
            ++a_cnt;
        }
        else
        {
            c = neigh;
        }
    }

    // Calculate number of neighbours of b equal to a and sert d vertex.
    for (auto e : b->get_edges())
    {
        Vertex* neigh { b->neighbour(e) };

        if (neigh == a)
        {
            ++b_cnt;
        }
        else
        {
            d = neigh;
        }
    }

    // Check parallel.
    if ((a_cnt != 2) || (b_cnt != 2))
    {
        return false;
    }

    // Check neighbours of a and b.
    if (c == d)
    {
        return false;
    }

    return true;
}

//
// Edge painting.
//

/// \brief Greedy paint.
///
/// Paint edges according to colors of all adjacent edges.
void
Edge::greedy_paint()
{
    utils::Colorable clr;
    Vertex* a { get_a() };
    Vertex* b { get_b() };
    const vector<Edge*>& ea = a->get_edges();
    const vector<Edge*>& eb = b->get_edges();

    for (auto f : ea)
    {
        int c { f->get_color() };

        if (c >= 0)
        {
            clr.paint(c);
        }
    }

    for (auto f : eb)
    {
        int c { f->get_color() };

        if (c >= 0)
        {
            clr.paint(c);
        }
    }

    int color { clr.first_free_color() };

    set_color(color);
}

/// @}

}
