/// \file
/// \brief Graph vertex implementation.
///
/// Graph vertex implementation.

#include "graph_vertex.h"

#include "graph_edge.h"
#include "utils/utils.h"
#include "mth/mth.h"

namespace graph
{

/// \addtogroup graph
/// @{

#ifdef DEBUG
// Counter initialization.
int Vertex::counter = 0;
#endif // DEBUG

/// \brief Constructor with identifier.
///
/// Only graph can create vertex.
///
/// \param[in] id_ Identier.
Vertex::Vertex(int id_)
    : id { id_ }
{

#ifdef DEBUG
   ++counter;
#endif // DEBUG

}

/// \brief Default destructor.
///
/// Default destructor.
Vertex::~Vertex()
{

#ifdef DEBUG
    --counter;
#endif // DEBUG

}

/// \brief Print function.
///
/// Print vertex information.
///
/// \param[in,out] os Output stream.
/// \param[in]     v  Vertex.
///
/// \return
/// Output stream.
ostream&
operator<<(ostream& os,
           const Vertex& v)
{
    os << "v" << v.id << " : edges(";

    for (size_t i = 0; i < v.edges_count(); ++i)
    {
        if (i > 0)
        {
            os << ",";
        }

        os << v.get_edge(i)->get_id();
    }

    os << ")";

    return os;
}

//
// Arrange.
//

/// \brief Arrange edges in identifiers increasing order.
///
/// Arrange edges in identifiers increasing order.
void
Vertex::arrange_edges_increasing_ids()
{
    sort(edges.begin(), edges.end(),
         [] (const Edge* e1, const Edge* e2)
         {
            return e1->get_id() < e2->get_id();
         });
}

//
// Relations with other elements.
//

/// \brief Check if vertex incident to edge.
///
/// Check if vertex incident to edge.
///
/// \param[in] e Edge.
///
/// \return
/// true - if vertex is incident to edge,
/// false - otherwise.
bool
Vertex::is_incident(const Edge* e) const
{
    for (auto x : edges)
    {
        if (x == e)
        {
            return true;
        }
    }

    return false;
}

/// \brief Get edge.
///
/// Get edge.
///
/// \param[in] i Number of edge.
///
/// \return
/// Edge.
Edge*
Vertex::get_edge(size_t i) const
{
    DEBUG_CHECK_ERROR(i < edges_count(), "wrong egde index (" + to_string(i) + ")");

    return edges[i];
}

/// \brief Get neighbour by edge.
///
/// Get neighbour by the edge.
///
/// \param[in] e Edge.
///
/// \return
/// Neighbour vertex.
Vertex*
Vertex::neighbour(const Edge* e) const
{
    Vertex* a { e->get_a() };
    Vertex* b { e->get_b() };

    if (this == a)
    {
        return b;
    }
    else if (this == b)
    {
        return a;
    }
    else
    {
        DEBUG_ERROR("edge e" + to_string(e->get_id())
                    + " and vertex v" + to_string(id) + " are not incident");

        return nullptr;
    }
}

/// \brief Find edge to another vertex.
///
/// Find edge to another vertex.
///
/// \param[in] v Vertex.
///
/// \return
/// Edge or nullptr.
Edge*
Vertex::find_edge(const Vertex* v) const
{
    for (auto e : edges)
    {
        if (neighbour(e) == v)
        {
            return e;
        }
    }

    return nullptr;
}

/// \brief Check if there is parallel edges from this vertex.
///
/// Check if there is parallel edges incident to this vertex.
///
/// \return
/// true - if there are two parallel edges incident to this vertex,
/// false - otherwise.
bool
Vertex::has_parallel_edges() const
{
    size_t cnt { edges_count() };

    for (size_t i = 0; i < cnt; ++i)
    {
        const Vertex* neighbour_i = neighbour(edges[i]);

        for (size_t j = i + 1; j < cnt; ++j)
        {
            const Vertex* neighbour_j = neighbour(edges[j]);

            if (neighbour_i == neighbour_j)
            {
                return true;
            }
        }
    }

    return false;
}

/// \brief Check if edges coloring is correct.
///
/// Check if edges coloring is correct.
///
/// \return
/// true - is edges coloring is correct,
/// false - otherwise.
bool
Vertex::is_edges_coloring_correct() const
{
    size_t cnt { edges_count() };

    for (size_t i = 0; i < cnt; ++i)
    {
        int c = edges[i]->get_color();

        for (size_t j = i + 1; j < cnt; ++j)
        {
            if (edges[j]->get_color() == c)
            {
                return false;
            }
        }
    }

    return true;
}

/// \brief Remove edge.
///
/// Remove edge.
/// \param[in,out] e Edge.
void
Vertex::remove_edge(Edge* e)
{
    auto it = find(edges.begin(), edges.end(), e);

    DEBUG_CHECK_ERROR(it != edges.end(), "edge not found and can not be removed");

    edges.erase(it);
}

/// @}

}
