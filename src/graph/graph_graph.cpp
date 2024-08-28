/// \file
/// \brief Graph implementation.
///
/// Graph implementation.

#include "graph_graph.h"

#include "graph_cubic_graph_reduce_history.h"
#include "mth/mth.h"

namespace caesar
{

namespace graph
{

/// \addtogroup graph
/// @{

#ifdef DEBUG
// Counter initialization.
int Graph::counter = 0;
#endif // DEBUG

/// \brief Default constructor.
///
/// Default constructor.
Graph::Graph()
{

#ifdef DEBUG
    ++counter;
#endif // DEBUG

}

/// \brief Default destructor.
///
/// Default destructor.
Graph::~Graph()
{
    // Delete vertices.
    for (auto v : vertices)
    {
        delete v;
    }

    // Delete edges.
    for (auto e : edges)
    {
        delete e;
    }

#ifdef DEBUG

    --counter;

    if (counter == 0)
    {
        // If last graph has been destructed, all subobjects must be destructed too.

        DEBUG_CHECK_ERROR(Vertex::counter == 0,
                          "live vertex after last graph destruction (counter = "
                          + to_string(Vertex::counter) + ")");
        DEBUG_CHECK_ERROR(Edge::counter == 0,
                          "live edge after last graph destruction (counter = "
                          + to_string(Edge::counter) + ")");
    }

#endif // DEBUG

}

/// \brief Print information.
///
/// \param[in,out] os Output stream.
void
Graph::print_info(ostream& os)
{
    os << "Graph:" << endl;

    //
    // Just print all elements.
    //

    os << "vertices:" << endl;

    for (auto v : vertices)
    {
        os << (*v) << endl;
    }

    os << "edges:" << endl;

    for (auto e : edges)
    {
        os << (*e) << endl;
    }
}

//
// Graph constructing.
//

/// \brief Get graph vertex.
///
/// Get graph vertex.
///
/// \param[in] i Index.
///
/// \return
/// Graph vertex.
Vertex*
Graph::get_vertex(size_t i) const
{
    DEBUG_CHECK_ERROR(i < order(), "wrong graph vertex index");

    return vertices[i];
}

/// \brief Get graph edge.
///
/// Get graph edge.
///
/// \param[in] i Index.
///
/// \return
/// Graph edge.
Edge*
Graph::get_edge(size_t i) const
{
    DEBUG_CHECK_ERROR(i < size(), "wrong graph edge index");

    return edges[i];
}

/// \brief Get random vertex.
///
/// \return
/// Random vertex.
Vertex*
Graph::get_random_vertex() const
{
    return get_vertex(static_cast<size_t>(mth::randint(0, static_cast<int>(order() - 1))));
}

/// \brief Get random edge.
///
/// \return
/// Random edge.
Edge*
Graph::get_random_edge() const
{
    return get_edge(static_cast<size_t>(mth::randint(0, static_cast<int>(size() - 1))));
}

/// \brief Find vertex by id.
///
/// Find vertex by id.
///
/// \param[in] id_ Identifier.
///
/// \return
/// Vertex of nullptr.
Vertex*
Graph::find_vertex_by_id(int id_) const
{
    for (auto v : vertices)
    {
        if (v->get_id() == id_)
        {
            return v;
        }
    }

    return nullptr;
}

/// \brief Find edge by id.
///
/// Find edge by id.
///
/// \param[in] id_ Identifier.
///
/// \return
/// Edge of nullptr.
Edge*
Graph::find_edge_by_id(int id_) const
{
    for (auto e : edges)
    {
        if (e->get_id() == id_)
        {
            return e;
        }
    }

    return nullptr;
}

/// \brief Create new vertex with given identifier.
///
/// Create new vertex with given identifier.
///
/// \param[in] id Identifier.
///
/// \return
/// New vertex.
Vertex*
Graph::new_vertex(int id)
{
    Vertex* v = new Vertex(id);

    vertices.push_back(v);

    return v;
}

/// \brief Add edge with given identifier between two vertices.
///
/// Add edge with given identifier between two vertices.
///
/// \param[in] a  First vertex.
/// \param[in] b  Second vertex.
/// \param[in] id Identifier
///
/// \return
/// New edge.
Edge*
Graph::add_edge(Vertex* a,
                Vertex* b,
                int id)
{
    Edge* e = new Edge(id);

    edges.push_back(e);

    a->add_edge(e);
    b->add_edge(e);

    if (a->get_id() < b->get_id())
    {
        e->add_vertex(a);
        e->add_vertex(b);
    }
    else
    {
        e->add_vertex(b);
        e->add_vertex(a);
    }

    return e;
}

/// \brief Add unique edge between two vertices.
///
/// Add edge but without creating parallel edges.
/// If there is already an edge between two vertices - return nullptr.
///
/// \param[in] a First vertex.
/// \param[in] b Second vertex.
///
/// \return
/// New edge,
/// or nullptr if there is already edge between vertices.
Edge*
Graph::add_unique_edge(Vertex* a,
                       Vertex* b)
{
    return has_edge(a, b) ? nullptr : add_edge(a, b);
}

/// \brief Add cycle for range of verties.
///
/// Add cycle to graph.
///
/// \param[in] fromi Lower index of vertex.
/// \param[in] toi   Higher index of vertex.
void
Graph::add_cycle(size_t fromi,
                 size_t toi)
{
    for (size_t i = fromi; i < toi; ++i)
    {
        add_edge(i, i + 1);
    }

    add_edge(fromi, toi);
}

/// \brief Check if graph contains parallel edges.
///
/// Check if graph contains parallel edges.
///
/// \return
/// true - if there are parallel edges in the graph,
/// false - otherwise.
bool
Graph::has_parallel_edges() const
{
    for (auto v : vertices)
    {
        if (v->has_parallel_edges())
        {
            return true;
        }
    }

    return false;
}

//
// Graph arranging.
//

/// \brief Reset identifiers.
void
Graph::reset_identifiers()
{
    size_t ord { order() }, siz { size() };

    for (size_t i = 0; i < ord; ++i)
    {
        vertices[i]->set_id(static_cast<int>(i));
    }

    for (size_t i = 0; i < siz; ++i)
    {
        edges[i]->set_id(static_cast<int>(i));
    }
}

/// \brief Arrange all objects in identifiers increasing order.
///
/// Arrange all objects in identifiers increasing order.
void
Graph::arrange_objects_increasing_ids()
{
    // Process all vertices.
    for (auto v : vertices)
    {
        v->arrange_edges_increasing_ids();
    }

    // Process all edges.
    for (auto e : edges)
    {
        e->arrange_vertices_increasing_ids();
    }

    // Arrange global lists.
    sort(vertices.begin(), vertices.end(),
         [] (const Vertex* v1, const Vertex* v2)
         {
            return v1->get_id() < v2->get_id();
         });
    sort(edges.begin(), edges.end(),
         [] (const Edge* e1, const Edge* e2)
         {
            return e1->get_id() < e2->get_id();
         });

    // Correct 
    max_vertex_id = vertices.back()->get_id();
    max_edge_id = edges.back()->get_id();
}

//
// Global properties.
//

/// \brief Check if graph is empty.
///
/// Graph is empty if it has no vertices and edges.
///
/// \return
/// true - if graph is empty,
/// false - otherwise.
bool
Graph::is_empty() const
{
    return (order() == 0) && (size() == 0);
}

/// \brief Check if graph is trivial.
///
/// Graph is trivial if it has only one vertex.
///
/// \return
/// true - if graph is trivial,
/// false - otherwise.
bool
Graph::is_trivial() const
{
    return (order() == 1) && (size() == 0);
}

/// \brief Check if graph is complete.
///
/// Graph is full if each vertex is connected with each one
/// with exacyly one edge
/// (graph with parallel edges is not compete).
///
/// \return
/// true - if graph is complete,
/// false - otherwise.
bool
Graph::is_complete() const
{
    size_t ord { order() };
    size_t siz { size() };

    if (siz != (ord * (ord - 1) / 2))
    {
        return false;
    }

    // Check edges between each pair of vertices.
    for (size_t i = 0; i < ord; ++i)
    {
        for (size_t j = i + 1; j < ord; ++j)
        {
            if (!has_edge(vertices[i], vertices[j]))
            {
                return false;
            }
        }
    }

    return true;
}

/// \brief Check if graph is regular.
///
/// Graph is regular if all vertices have the same degree.
///
/// \return
/// true - if graph is regular,
/// false - otherwise.
bool
Graph::is_regular(size_t d) const
{
    for (auto v : vertices)
    {
        if (v->degree() != d)
        {
            return false;
        }
    }

    return true;
}

/// \brief Check graph is minimal cubic.
///
/// Check graph is minimal cubic.
///
/// \return
/// true - if graph is minimal cubic graph,
/// false - otherwise.
bool
Graph::is_minimal_cubic() const
{
    return (order() == 2) && (size() == 3);
}

/// \brief Check for strong isomorphic of two graphs.
///
/// Check for string isomorphic of two graphs.
///
/// \param[in] g1 First graph.
/// \param[in] g2 Second graph.
///
/// \return
/// true - if two graphs are strong isomorpic,
/// false - otherwise.
bool
Graph::is_strong_isomorphic(const Graph& g1,
                            const Graph& g2)
{
    size_t ord { g1.order() };
    size_t siz { g1.size() };

    if ((g2.order() != ord) || (g2.size() != siz))
    {
        return false;
    }

    // Check each vertex links with edges.
    for (size_t i = 0; i < ord; ++i)
    {
        Vertex* v1 = g1.get_vertex(i);
        Vertex* v2 = g2.get_vertex(i);
        size_t deg { v1->degree() };

        if ((v1->get_id() != v2->get_id()) || (v2->degree() != deg))
        {
            return false;
        }

        for (size_t j = 0; j < deg; ++j)
        {
            if (v1->get_edge(j)->get_id() != v2->get_edge(j)->get_id())
            {
                return false;
            }
        }
    }

    // Check each edge links with vertices.
    for (size_t i = 0; i < siz; ++i)
    {
        Edge* e1 = g1.get_edge(i);
        Edge* e2 = g2.get_edge(i);

        if ((e1->get_id() != e2->get_id())
            || (e1->get_a()->get_id() != e2->get_a()->get_id())
            || (e1->get_b()->get_id() != e2->get_b()->get_id()))
        {
            return false;
        }
    }

    return true;
}

//
// Graph modifications.
//

/// \brief Remove edge from graph.
///
/// Remove edge from graph.
///
/// \param[in,out] e Edge.
void
Graph::remove_edge(Edge* e)
{
    Vertex* a { e->get_a() };
    Vertex* b { e->get_b() };

    // Remove from vertices.
    a->remove_edge(e);
    b->remove_edge(e);

    // Remove from global list.

    auto it = find(edges.begin(), edges.end(), e);

    DEBUG_CHECK_ERROR(it != edges.end(), "edge not found and can not be removed");

    edges.erase(it);

    // Finally free memory.
    delete e;
}

/// \brief Remove vertex from graph.
///
/// Remove vertex from graph.
///
/// \param[in,out] v Vertex.
void
Graph::remove_vertex(Vertex* v)
{
    while (v->degree())
    {
        remove_edge(v->get_edge(0));
    }

    // Find vertex in global list and remove.

    auto it = find(vertices.begin(), vertices.end(), v);

    DEBUG_CHECK_ERROR(it != vertices.end(), "vertex not found and can not be removed");

    vertices.erase(it);

    // Free memory.
    delete v;
}

/// \brief Bubble cubic graph vertex.
///
/// Bubble cubic graph vertex.
///
/// \param[in] v Vertex.
void
Graph::bubble_cubic_graph_vertex(Vertex* v)
{
    DEBUG_CHECK_ERROR(v->degree() == 3, "bubble is possible only for vertex with degree 3");

    Edge* ea = v->get_edge(0);
    Edge* eb = v->get_edge(1);
    Edge* ec = v->get_edge(2);
    Vertex* a = v->neighbour(ea);
    Vertex* b = v->neighbour(eb);
    Vertex* c = v->neighbour(ec);

    // Remove vertex.
    remove_vertex(v);

    // Add 3-cycle instead it.
    Vertex* na = new_vertex();
    Vertex* nb = new_vertex();
    Vertex* nc = new_vertex();
    add_edge(a, na);
    add_edge(b, nb);
    add_edge(c, nc);
    add_edge(na, nb);
    add_edge(nb, nc);
    add_edge(na, nc);
}

/// \brief Bubble cubic graph vertex.
///
/// Bubble random graph vertex.
void
Graph::bubble_cubic_graph_vertex()
{
    bubble_cubic_graph_vertex(get_random_vertex());
}

//
// Cubic graph reduce and restore.
//

/// \brief Glue two edges incodent to vertex.
///
/// Glue two edges incident to vertex.
///
///         e1       e2
///     C ------ v ------ D  ==>  C ------ D
///
/// \param[in,out] v     Vertex.
/// \param[out]    e1_id Identifier of the first edge.
/// \param[out]    e2_id Identifier of the second edge.
///
/// \return
/// New edge.
Edge*
Graph::glue_two_incident_edges(Vertex* v,
                               int& e1_id,
                               int& e2_id)
{
    DEBUG_CHECK_ERROR(v->degree() == 2, "can not glue number of edges differ from 2");

    Edge* ea { v->get_edge(0) };
    Edge* eb { v->get_edge(1) };
    Vertex* a { v->neighbour(ea) };
    Vertex* b { v->neighbour(eb) };

    // For new edge identifiers of end are sorted in increasing order.
    // Here we have to make sure order of initial edges is saved.
    if (a->get_id() < b->get_id())
    {
        e1_id = ea->get_id();
        e2_id = eb->get_id();
    }
    else
    {
        e1_id = eb->get_id();
        e2_id = ea->get_id();
    }

    // Remove old edges.
    remove_edge(ea);
    remove_edge(eb);

    // Add new edge.
    Edge* new_edge = add_edge(a, b);

    // Remove vertex.
    remove_vertex(v);

    return new_edge;
}

/// \brief Glue two hanging edges.
///
/// Glue two hanging edges.
///
///        v1_e1             v2_e1
///     C ------- v1     v2 ------- D  ==>  C ------ D
///
/// \param[in,out] v1                   First vertex.
/// \param[in,out] v2                   Second vertex.
/// \param[out]    is_new_edge_reversed Flag if new edge changes vertices order.
///
/// \return
/// New edge.
Edge*
Graph::glue_two_hanging_edges(Vertex* v1,
                              Vertex* v2,
                              bool& is_new_edge_reversed)
{
    DEBUG_CHECK_ERROR(v1->is_leaf() && v2->is_leaf(), "one or two edges are not hanging");

    // Take vertices for new edge.
    Edge* v1_e1 { v1->get_edge(0) };
    Edge* v2_e1 { v2->get_edge(0) };
    Vertex* a { v1->neighbour(v1_e1) };
    Vertex* b { v2->neighbour(v2_e1) };

    // New edge will be added with vertices in identifiers increasing order,
    // so save edges identifiers correctly.
    is_new_edge_reversed = (a->get_id() > b->get_id());

    // Remove old edges.
    remove_edge(v1_e1);
    remove_edge(v2_e1);

    // Add new edge.
    Edge* new_edge = add_edge(a, b);

    // Remove old vertices.
    remove_vertex(v1);
    remove_vertex(v2);

    return new_edge;
}

/// \brief Get cubic graph unique reduceable edge.
///
/// Get edge for cubic graph which is unique and can ce used for reduce.
///
/// \return
/// Edge for reduce or nullptr.
Edge*
Graph::get_cubic_graph_unique_reduceable_edge()
{
    for (auto e : edges)
    {
        if (e->is_cubic_graph_unique_reduceable_edge())
        {
            return e;
        }
    }

    return nullptr;
}

/// \brief Get cubuc graph parallel reduceable edge.
///
/// Get cubic graph parallel reduceable edge.
///
/// \return
/// Cubic graph parallel reduceable edge.
Edge*
Graph::get_cubic_graph_parallel_reduceable_edge()
{
    for (auto e : edges)
    {
        if (e->is_cubic_graph_parallel_reduceable_edge())
        {
            return e;
        }
    }

    return nullptr;
}

/// \brief Reduce cubic graph by unique edge.
///
/// Reduce cubic graph by unique edge.
///
///       v1_e1              v2_e1
///     C -----*            *----- E       C ---*           *--- E
///            |     e      |                   | re1       |
///         v1 A ---------- B v2      ==>       |           |
///            |            |                   |       re2 |
///     D -----*            *----- F       D ---*           *--- F
///       v1_e2              v2_e2
///
/// \param[in,out] e Edge.
/// \param[in,out] h History.
void
Graph::reduce_cubic_graph_by_unique_edge(Edge* e,
                                         CubicGraphReduceHistory* h)
{
    DEBUG_CHECK_ERROR(e->is_cubic_graph_unique_reduceable_edge(), "edge is not unique reduceable in cubic graph");

    // Save ends and identifier.
    Vertex* a { e->get_a() };
    Vertex* b { e->get_b() };
    int e_id { e->get_id() };

    remove_edge(e);
    DEBUG_CHECK_ERROR(a->degree() == 2, "trying to reduce by edge for non cubic graph");
    DEBUG_CHECK_ERROR(b->degree() == 2, "trying to reduce by edge for non cubic graph");

    // Save all related ids.
    int v1_id { a->get_id() };
    int v2_id { b->get_id() };
    int v1_e1_id { 0 };
    int v1_e2_id { 0 };
    int v2_e1_id { 0 };
    int v2_e2_id { 0 };

    // Glue edges.
    Edge* new_e1 = glue_two_incident_edges(a, v1_e1_id, v1_e2_id);
    Edge* new_e2 = glue_two_incident_edges(b, v2_e1_id, v2_e2_id);

    if (h != nullptr)
    {
        h->remember(v1_id, v2_id, e_id,
                    v1_e1_id, v1_e2_id, v2_e1_id, v2_e2_id,
                    new_e1->get_id(), new_e2->get_id());
    }
}

/// \brief Reduce cubic graph graph by parallel edge.
///
/// Reduce cubic graph by parallel edge.
///
///                   e
///             *-----------*
///       v1_e1 |           | v2_e1            re1 = re2
///     C ----- A (v1) (v2) B ----- D  ==>  C ----------- D
///             |           |
///             *-----------*
///                   e2
///
/// \param[in,out] e Edge.
/// \param[in,out] h History.
void
Graph::reduce_cubic_graph_by_parallel_edge(Edge* e,
                                           CubicGraphReduceHistory* h)
{
    DEBUG_CHECK_ERROR(e->is_cubic_graph_parallel_reduceable_edge(), "edge is not parallel reduceable in cubic graph");

    // Save ends and identifier.
    Vertex* v1 { e->get_a() };
    Vertex* v2 { e->get_b() };
    int e_id { e->get_id() };

    // Remove edge.
    remove_edge(e);
    DEBUG_CHECK_ERROR(v1->degree() == 2, "trying to reduce by edge for non cubic graph");
    DEBUG_CHECK_ERROR(v1->degree() == 2, "trying to reduce by edge for non cubic graph");

    // Find duplicate edge and save its identifier.
    Edge* e2 { find_edge(v1, v2) };
    DEBUG_CHECK_ERROR(e2 != nullptr, "no duplicate edge is found");
    int e2_id { e2->get_id() };

    // Remove duplicate edge too.
    remove_edge(e2);

    // Save vertices identifiers.
    int v1_id { v1->get_id() };
    int v2_id { v2->get_id() };
    int v1_e1_id { v1->get_edge(0)->get_id() };
    int v2_e1_id { v2->get_edge(0)->get_id() };

    // Glue edges.
    bool is_new_edge_reversed { false };
    Edge* new_e { glue_two_hanging_edges(v1, v2, is_new_edge_reversed) };

    if (h != nullptr)
    {
        int new_e_id { new_e->get_id() };

        if (!is_new_edge_reversed)
        {
            h->remember(v1_id, v2_id, e_id,
                        v1_e1_id, e2_id, v2_e1_id, e2_id,
                        new_e_id, new_e_id);
        }
        else
        {
            h->remember(v2_id, v1_id, e_id,
                        v2_e1_id, e2_id, v1_e1_id, e2_id,
                        new_e_id, new_e_id);
        }
    }
}

/// \brief Full reduce cubic graph.
///
/// Full reduce cubic graph.
///
/// \return
/// Count of steps.
int
Graph::full_reduce_cubic_graph(CubicGraphReduceHistory* h)
{
    int cnt { 0 };
    Edge* e { nullptr };

    while (true)
    {
        e = get_cubic_graph_unique_reduceable_edge();

        if (e != nullptr)
        {
            reduce_cubic_graph_by_unique_edge(e, h);
        }
        else
        {
            e = get_cubic_graph_parallel_reduceable_edge();

            if (e != nullptr)
            {
                reduce_cubic_graph_by_parallel_edge(e, h);
            }
            else
            {
                // No reduceable edges anymore.
                break;
            }
        }

        ++cnt;
    }

    return cnt;
}

/// \brief Restore cubic graph step for unique edge.
///
/// Restore cubic graph step for unique edge.
///
/// \param[in] h History.
void
Graph::restore_cubic_graph_step_unique_edge(const CubicGraphReduceHistory& h)
{
    DEBUG_CHECK_ERROR(h.get().is_reduce_by_unique_edge(), "restore by unique edge can not be applied");

    int v1_id { h.get_v1_id() };
    int v2_id { h.get_v2_id() };
    int e_id { h.get_e_id() };
    int v1_e1_id { h.get_v1_e1_id() };
    int v1_e2_id { h.get_v1_e2_id() };
    int v2_e1_id { h.get_v2_e1_id() };
    int v2_e2_id { h.get_v2_e2_id() };
    int result_e1_id { h.get_result_e1_id() };
    int result_e2_id { h.get_result_e2_id() };

    // First we add two new vertices with given identifiers.
    // Add edge between these two vertices.
    Vertex* v1 { new_vertex(v1_id) };
    Vertex* v2 { new_vertex(v2_id) };

    // Find result edges.
    Edge* result_e1 { find_edge_by_id(result_e1_id) };
    Edge* result_e2 { find_edge_by_id(result_e2_id) };

    // Add all old deleted edges.
    add_edge(v1, v2, e_id);
    add_edge(v1, result_e1->get_a(), v1_e1_id);
    add_edge(v1, result_e1->get_b(), v1_e2_id);
    add_edge(v2, result_e2->get_a(), v2_e1_id);
    add_edge(v2, result_e2->get_b(), v2_e2_id);

    // Remove edges from step of history.
    remove_edge(result_e1);
    remove_edge(result_e2);
}

/// \brief Restore cubic graph step for parallel edge.
///
/// Restore cubic graph step for parallel edge.
void
Graph::restore_cubic_graph_step_parallel_edge(const CubicGraphReduceHistory& h)
{
    DEBUG_CHECK_ERROR(h.get().is_reduce_by_parallel_edge(), "restore by parallel edge can not be applied");

    int v1_id { h.get_v1_id() };
    int v2_id { h.get_v2_id() };
    int e_id { h.get_e_id() };
    int e2_id { h.get_v1_e2_id() };

    DEBUG_CHECK_ERROR(h.get_v1_e2_id() == h.get_v2_e2_id(), "second edges for both vertices must be equal");

    int v1_e1_id { h.get_v1_e1_id() };
    int v2_e1_id { h.get_v2_e1_id() };
    int result_e1_id { h.get_result_e1_id() };

    DEBUG_CHECK_ERROR(result_e1_id == h.get_result_e2_id(), "it must be only one result edge");

    // First we add two new vertices with given identifiers.
    // Add edge between these two vertices.
    Vertex* v1 { new_vertex(v1_id) };
    Vertex* v2 { new_vertex(v2_id) };

    // Find result edge.
    Edge* result_e { find_edge_by_id(result_e1_id) };

    // Add all old deleted edges.
    add_edge(v1, v2, e_id);
    add_edge(v1, v2, e2_id);
    add_edge(v1, result_e->get_a(), v1_e1_id);
    add_edge(v2, result_e->get_b(), v2_e1_id);

    // Remove edge from step of history.
    remove_edge(result_e);
}

/// \brief Restore cubic graph one step.
///
/// Restore cubic graph history.
///
/// \param[in] h History of reduce.
void
Graph::restore_cubic_graph_step(CubicGraphReduceHistory& h)
{
    DEBUG_CHECK_ERROR(!h.is_empty(), "can not restore from empty history");

    const CubicGraphReduceHistoryStep& step { h.get() };

    if (step.is_reduce_by_unique_edge())
    {
        restore_cubic_graph_step_unique_edge(h);
    }
    else
    {
        restore_cubic_graph_step_parallel_edge(h);
    }

    h.pop();
}

/// \brief Restore cubic graph (all steps).
///
/// Restore cubic graph (all steps of history).
///
/// \param[in] h History of reduce.
void
Graph::restore_cubic_graph(CubicGraphReduceHistory& h)
{
    while (!h.is_empty())
    {
        restore_cubic_graph_step(h);
    }

    arrange_objects_increasing_ids();
}

//
// Graph coloring.
//

/// \brief Fill edges colors histogram.
///
/// Fill edges colors histogram.
///
/// \param[in,out] h Histogram.
void
Graph::fill_edges_colors_histogram(vector<int>& h) const
{
    for (auto e : edges)
    {
        int color = e->get_color();

        if (color < 0)
        {
            continue;
        }

        size_t scolor = static_cast<size_t>(color);

        while (h.size() <= scolor)
        {
            h.push_back(0);
        }

        ++h[scolor];
    }
}

/// \brief Greedy graph coloring.
///
/// Analyze each edge and paint it with first free color
/// (color differs from colors of all adjacent edges).
///
/// \return
/// Number of colors used.
int
Graph::edges_coloring_greedy()
{
    int max_color { -1 };

    // First paint all edges with color 0.
    for (auto e : edges)
    {
        e->set_color(-1);
    }

    // For each edge just paint it with first free color.
    for (auto e : edges)
    {
        e->greedy_paint();
        max_color = max(max_color, e->get_color());
    }

    // Check coloring.
    DEBUG_CHECK_ERROR(is_edges_coloring_correct(), "greedy edges coloring fault");

    return max_color + 1;
}

/// \brief Restore and repaint cubic graph step for unique edge.
///
/// Restore and repaint cubic graph step for unique edge.
/// Restoring and repainting is possible only when both result edges lay on single bicolor cycle.
///
/// \param[in]     h         History of reduce.
/// \param[in,out] bc        Bicolor cycle.
/// \param[in,out] result_e1 First edge.
/// \param[in,out] result_e2 Second edge.
void
Graph::restore_and_repaint_cubic_graph_step_unique_edge(const CubicGraphReduceHistory& h,
                                                        BicolorCycle& bc,
                                                        Edge* result_e1,
                                                        Edge* result_e2)
{
    DEBUG_CHECK_ERROR(bc.has(result_e1) && bc.has(result_e2), "bicolor cycle must contain both edges");

    // Get identifiers of all edged we will repaint.
    int e_id { h.get_e_id() };
    int v1_e1_id { h.get_v1_e1_id() };
    int v1_e2_id { h.get_v1_e2_id() };
    int v2_e1_id { h.get_v2_e1_id() };
    int v2_e2_id { h.get_v2_e2_id() };

    // Save color for restores edge.
    // Save it before repaint cycle.
    int e_color { 3 - bc.sum_colors() };

    // Switch colors between result edges.
    bc.switch_colors(result_e1, result_e2);

    // Restore graph step.
    restore_cubic_graph_step_unique_edge(h);

    // Repaint restored edges.
    find_edge_by_id(e_id)->set_color(e_color);
    Edge* v1_e1 { find_edge_by_id(v1_e1_id) };
    Edge* v1_e2 { find_edge_by_id(v1_e2_id) };
    Edge* v2_e1 { find_edge_by_id(v2_e1_id) };
    Edge* v2_e2 { find_edge_by_id(v2_e2_id) };

    // TODO: we need to perform more accurate repaint.
    v1_e1->greedy_paint();
    v1_e2->greedy_paint();
    v2_e1->greedy_paint();
    v2_e2->greedy_paint();

    DEBUG_CHECK_ERROR(e_color < 3, "we can use only [0-2] colors");
    DEBUG_CHECK_ERROR(v1_e1->get_color() < 3, "we can use only [0-2] colors");
    DEBUG_CHECK_ERROR(v1_e2->get_color() < 3, "we can use only [0-2] colors");
    DEBUG_CHECK_ERROR(v2_e1->get_color() < 3, "we can use only [0-2] colors");
    DEBUG_CHECK_ERROR(v2_e2->get_color() < 3, "we can use only [0-2] colors");
}

/// \brief Restore and repaint cubic graph step for unique edge when colors are equal.
///
/// Restore anf repaint cubic graph for unique edge when colors of result edges are equal.
///
/// \param[in]     h         History.
/// \param[in,out] result_e1 First edge.
/// \param[in,out] result_e2 Second edge.
void
Graph::restore_and_repaint_cubic_graph_step_unique_edge_eq_colors(const CubicGraphReduceHistory& h,
                                                                  Edge* result_e1,
                                                                  Edge* result_e2)
{
    DEBUG_CHECK_ERROR(result_e1->get_color() == result_e2->get_color(), "edges must be the same color");

    vector<int> other_colors;

    // Get colors to try make bicolor cycles.
    for (int i = 0; i < 3; ++i)
    {
        if (i != result_e1->get_color())
        {
            other_colors.push_back(i);
        }
    }

    // Try both colors.
    for (auto another_color : other_colors)
    {
        BicolorCycle bc;

        bc.build(result_e1, another_color);

        if (bc.has(result_e2))
        {
            restore_and_repaint_cubic_graph_step_unique_edge(h, bc, result_e1, result_e2);

            return;
        }
    }

    DEBUG_ERROR("impossible to restore graph with Tait coloring");
}

/// \brief Restore and repaint cubic graph step for unique edge colors are not equal.
///
/// Restore and repaint cubic graph unique edge when colors of result edges are not equal.
///
/// \param[in]     h         History.
/// \param[in,out] result_e1 First edge.
/// \param[in,out] result_e2 Second edge.
void
Graph::restore_and_repaint_cubic_graph_step_unique_edge_ne_colors(const CubicGraphReduceHistory& h,
                                                                  Edge* result_e1,
                                                                  Edge* result_e2)
{
    DEBUG_CHECK_ERROR(result_e1->get_color() != result_e2->get_color(), "edges must not be the same color");

    BicolorCycle bc;

    bc.build(result_e1, result_e2->get_color());

    if (bc.has(result_e2))
    {
        // Everything is all right.
        // Both edges are places on single bicolor cycle, we can repaint graph.
        restore_and_repaint_cubic_graph_step_unique_edge(h, bc, result_e1, result_e2);
    }
    else
    {
        // If we repaint bicolor cycle, then result edges will be the same color.
        bc.switch_colors();
        restore_and_repaint_cubic_graph_step_unique_edge_eq_colors(h, result_e1, result_e2);
    }
}

/// \brief Restore and repaint cubic graph step for unique edge.
///
/// Restore and repaint cubic graph step for unique edge.
///
/// \param[in] h History.
void
Graph::restore_and_repaint_cubic_graph_step_unique_edge(const CubicGraphReduceHistory& h)
{
    // We need both result edges to analyze.
    Edge* result_e1 { find_edge_by_id(h.get_result_e1_id()) };
    Edge* result_e2 { find_edge_by_id(h.get_result_e2_id()) };

    // We have different methods to repaint for
    // color1 == color2 and color1 != color2 cases.
    if (result_e1->get_color() == result_e2->get_color())
    {
        restore_and_repaint_cubic_graph_step_unique_edge_eq_colors(h, result_e1, result_e2);
    }
    else
    {
        restore_and_repaint_cubic_graph_step_unique_edge_ne_colors(h, result_e1, result_e2);
    }
}

/// \brief Restore and repaint cubic graph step for parallel edge.
///
/// Restore and repaint cubic graph step for parallel edge.
///
/// \param[in] h History.
void
Graph::restore_and_repaint_cubic_graph_step_parallel_edge(const CubicGraphReduceHistory& h)
{
    // We have to remember color of result edge.
    // It will be used for v1_e1 and v2_e1 edges coloring.
    int result_e_color { find_edge_by_id(h.get_result_e1_id())->get_color() };

    // Get edges identifiers which will be repainted.
    int e_id { h.get_e_id() };
    int v1_e1_id { h.get_v1_e1_id() };
    int v1_e2_id { h.get_v1_e2_id() };
    int v2_e1_id { h.get_v2_e1_id() };

    // Restore step.
    restore_cubic_graph_step_parallel_edge(h);

    // Edges v1_e1 and v2_e1 keep result edge color.
    find_edge_by_id(v1_e1_id)->set_color(result_e_color);
    find_edge_by_id(v2_e1_id)->set_color(result_e_color);

    // Rest edges repainted in greedy manner.
    find_edge_by_id(v1_e2_id)->greedy_paint();
    find_edge_by_id(e_id)->greedy_paint();
}

/// \brief Edges coloring for cubic graph using bicolor cycles.
///
/// Edges coloring for cubic graph using bicolor cycles.
void
Graph::edges_coloring_for_cubic_graph_with_bicolor_cycles_algorithm()
{
    DEBUG_CHECK_ERROR(is_cubic(), "bicolor cycles algorithm is applicable only for cubic graphs");

    CubicGraphReduceHistory h;

    // Full reduce to minimal cubic graph.
    full_reduce_cubic_graph(&h);

    DEBUG_CHECK_ERROR(is_minimal_cubic(), "reducing to minimal cubic graph faul");

    // Set colors for minimal cubic graph.
    for (size_t i = 0; i < size(); ++i)
    {
        get_edge(i)->set_color(static_cast<int>(i));
    }

    // Restore graph from history.
    while (!h.is_empty())
    {
        const CubicGraphReduceHistoryStep& step { h.get() };

        if (step.is_reduce_by_unique_edge())
        {
            restore_and_repaint_cubic_graph_step_unique_edge(h);
        }
        else
        {
            restore_and_repaint_cubic_graph_step_parallel_edge(h);
        }

        h.pop();
    }

    arrange_objects_increasing_ids();

    // Check coloring.
    DEBUG_CHECK_ERROR(is_edges_coloring_correct(), "greedy edges coloring fault");
}

/// \brief Check if edges coloring is correct.
///
/// Check if edges coloring is correct.
///
/// \return
/// true - if edges coloring is correct,
/// false - otherwise.
bool
Graph::is_edges_coloring_correct() const
{
    for (auto v : vertices)
    {
        if (!v->is_edges_coloring_correct())
        {
            return false;
        }
    }

    return true;
}

/// @}

}

}
