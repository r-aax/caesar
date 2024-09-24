/// \file
/// \brief Unstructured surface mesh implementation.
///
/// Implementation of unstructured surface mesh.

#include "mesh_mesh.h"

#include "utils/utils.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

//
// Control memory leaks.
//

#ifdef DEBUG
// Counter initialization.
int Mesh::counter = 0;
#endif // DEBUG

//
// Constructors/destructors.
//

/// \brief Default constructor.
Mesh::Mesh()
    : own_edges_by_colors(max_edges_colors_count, vector<Edge*>()),
      own_edges_colors_histogram(max_edges_colors_count, 0)
{

#ifdef DEBUG
    ++counter;
#endif // DEBUG

}

/// \brief Default destructor.
Mesh::~Mesh()
{
    // Delete nodes.
    for (auto n : all.nodes())
    {
        delete n;
    }

    // Delete edges.
    for (auto e : all.edges())
    {
        delete e;
    }

    // Delete cells.
    for (auto c : all.cells())
    {
        delete c;
    }

    // Delete zones.
    for (auto z : zones)
    {
        delete z;
    }

#ifdef DEBUG

    --counter;

    if (counter == 0)
    {
        // If last mesh has been destructed, all subobjects must be destructed too.

        DEBUG_CHECK_ERROR(Node::counter == 0,
                          "live node after last mesh destruction (counter = "
                          + to_string(Node::counter) + ")");
        DEBUG_CHECK_ERROR(Edge::counter == 0,
                          "live edge after last mesh destruction (counter = "
                          + to_string(Edge::counter) + ")");
        DEBUG_CHECK_ERROR(Cell::counter == 0,
                          "live cell after last mesh destruction (counter = "
                          + to_string(Cell::counter) + ")");
        DEBUG_CHECK_ERROR(Zone::counter == 0,
                          "live zone after last mesh destruction (counter = "
                          + to_string(Zone::counter) + ")");
    }

#endif // DEBUG

}

//
// Print funtions.
//

/// \brief Print information.
///
/// Print information.
///
/// \param[in] s                 Stream.
/// \param[in] is_print_elements Flag for printing nodes/edges/cells.
void
Mesh::print_info(ostream& s,
                 bool is_print_elements) const
{
    s << "UnstructuredSurfaceMesh" << endl;
    s << "Title                      : " << title << endl;
    s << "Variables names            :";

    for (auto& vn : variables_names)
    {
        s << " \"" << vn << "\"";
    }

    s << endl;
    s << "Varlocation cellcentered   : "
      << varlocation_cellcentered.first << " " << varlocation_cellcentered.second << endl;
    s << "Nodes vector size          : " << all.nodes_count() << endl;
    s << "Edges vector size          : " << all.edges_count() << endl;
    s << "Own edges vector size      : " << own.edges_count() << endl;
    s << "Own edges colors histogram :";

    int total_edges_colors_count { 0 };

    for (size_t i = 0; i < max_edges_colors_count; ++i)
    {
        s << " " << own_edges_colors_histogram[i];
        total_edges_colors_count += own_edges_colors_histogram[i];
    }

    s << " : total = " << total_edges_colors_count << endl;

    s << "Cells vector size          : " << all.cells_count() << endl;
    s << "Own cells vector size      : " << own.cells_count() << endl;
    s << "............................" << endl;
    s << "Zones count                : " << zones.size() << endl;

    for (auto zone : zones)
    {
        zone->print_info(s);
    }

    if (is_print_elements)
    {
        vector<int> full { numeric_limits<int>::min(), numeric_limits<int>::max() };

        print_elements(full, full, full, s);
    }
}

/// \brief Print mesh elements.
///
/// Print mesh elements : nodes, edges, cells.
///
/// \param[in] nodes_ids_range Range of nodes identifiers to print.
/// \param[in] edges_ids_range Range of edges identifiers to print.
/// \param[in] cells_ids_range Range of cellss identifiers to print.
/// \param[in] s               Stream.
void
Mesh::print_elements(const vector<int>& nodes_ids_range,
                     const vector<int>& edges_ids_range,
                     const vector<int>& cells_ids_range,
                     ostream& s) const
{
    for (auto n : all.nodes())
    {
        if (mth::in_bounds(n->get_id(), nodes_ids_range))
        {
            s << (*n) << endl;
        }
    }

    for (auto e : all.edges())
    {
        if (mth::in_bounds(e->get_id(), edges_ids_range))
        {
            s << (*e) << endl;
        }
    }

    for (auto c : all.cells())
    {
        if (mth::in_bounds(c->get_id(), cells_ids_range))
        {
            s << (*c) << endl;
        }
    }
}

//
// Init identifiers.
//

/// \brief Init global identifiers.
void
Mesh::init_global_identifiers()
{
    #pragma omp parallel for
    for (size_t i = 0; i < all.nodes_count(); ++i)
    {
        all.node(i)->set_id(static_cast<int>(i));
    }

    #pragma omp parallel for
    for (size_t i = 0; i < all.edges_count(); ++i)
    {
        all.edge(i)->set_id(static_cast<int>(i));
    }

    #pragma omp parallel for
    for (size_t i = 0; i < all.cells_count(); ++i)
    {
        all.cell(i)->set_id(static_cast<int>(i));
    }
}

/// \brief Init local identifiers.
void
Mesh::init_local_identifiers()
{
    #pragma omp parallel for
    for (size_t i = 0; i < own.edges_count(); ++i)
    {
        own.edge(i)->set_loc_id(static_cast<int>(i));
    }

    #pragma omp parallel for
    for (size_t i = 0; i < own.cells_count(); ++i)
    {
        own.cell(i)->set_loc_id(static_cast<int>(i));
    }
}

/// \brief Register edge's color.
///
/// Set color to the edges.
/// Add color to histogramm.
/// Add edge to its vector.
///
/// \param[in,out] e Edge.
/// \param[in]     c Color.
void
Mesh::register_edge_color(Edge* e,
                          int c)
{
    e->set_color(c);

    // Add to histogram.
    add_color_to_own_edges_colors_histogram(c);

    // Add to vector of color.
    own_edges_by_colors[static_cast<size_t>(c)].push_back(e);
}

/// \brief Check own edges colors distribution correctness.
///
/// Check if own edges colors distribution is correct.
///
/// \return
/// true - if edges colors distribution is correct,
/// false - otherwise.
bool
Mesh::is_own_edges_colors_distribution_correct() const
{
    size_t cnt { own.edges_count() };
    size_t vec_cnt { 0 }, hist_cnt { 0 };

    for (size_t i = 0; i < max_edges_colors_count; ++i)
    {
        vec_cnt += own_edges_by_colors[i].size();
        hist_cnt += static_cast<size_t>(own_edges_colors_histogram[i]);
    }

    return (cnt == vec_cnt) && (cnt == hist_cnt);
}

//
// Set variables names for mesh storing.
//

/// \brief Set variables names.
///
/// Set variables names.
///
/// \param[in] nodes_variables_names Nodes variables names.
/// \param[in] cells_variables_names Cells variables names.
void
Mesh::set_variables_names(const vector<string>& nodes_variables_names,
                          const vector<string>& cells_variables_names)
{
    variables_names.clear();

    // Copy names from nodes variables names.
    for (auto s : nodes_variables_names)
    {
        variables_names.push_back(s);
    }

    // Copy names from cells variables names.
    for (auto s : cells_variables_names)
    {
        variables_names.push_back(s);
    }

    // Correct cellcentered data.
    varlocation_cellcentered.first = nodes_variables_names.size() + 1;
    varlocation_cellcentered.second = variables_names.size();
}

//
// Objects links.
//

/// \brief Find zone.
///
/// Find zone by name.
///
/// \param[in] name Zone name.
///
/// \return
/// Found zone or nullptr.
Zone*
Mesh::find_zone(const string& name) const
{
    for (Zone* zone : zones)
    {
        if (zone->name == name)
        {
            return zone;
        }
    }

    return nullptr;
}

/// \brief Find node.
///
/// Find node strictly based on given point.
///
/// \param[in] point Point.
///
/// \return
/// Pointer to node of nullptr (if node is not found).
Node*
Mesh::find_node(const geom::Vector& point) const
{
    for (auto node : all.nodes())
    {
        if (node->point().is_strict_eq(point))
        {
            return node;
        }
    }

    return nullptr;
}

/// \brief Distribute edges between zones.
///
/// Each edge is passed to zones of its incident cells.
void
Mesh::distribute_edges_between_zones()
{
    for (auto e : all.edges())
    {
        size_t cn = e->cells_count();

        DEBUG_CHECK_ERROR((cn == 1) || (cn == 2), "wrong count of incident cells for edge");

        Zone* z0 = e->cell(0)->zone;

        z0->add_edge(e);

        if (cn > 1)
        {
            Zone* z1 = e->cell(1)->zone;

            if (z1 != z0)
            {
                z1->add_edge(e);
            }
        }
    }
}

/// \brief Init cells neighbourhoods.
///
/// Init neighbourhood for each cell.
void
Mesh::init_cells_neighbourhoods()
{
    #pragma omp parallel for
    for (auto cell : all.cells())
    {
        cell->init_neighbourhood();
    }
}

//
// Mark functions.
//

/// \brief Mark cells.
///
/// Mark cells.
///
/// \param[in] cond Condition for mark.
void
Mesh::mark_cells(bool (*cond)(Cell*))
{
    #pragma omp parallel for
    for (auto c : all.cells())
    {
        c->set_mark(cond(c) ? 1 : 0);
    }
}

/// \brief Mark border nodes and cells.
///
/// Mark border nodes and cells.
void
Mesh::mark_mesh_border_nodes_and_cells()
{
    #pragma omp parallel for
    for (auto node : all.nodes())
    {
        node->set_mark(1);
    }

    #pragma omp parallel for
    for (auto cell : all.cells())
    {
        cell->set_mark(1);
    }
}

//
// Geometry.
//

/// \brief Calculate geometry.
///
/// Calculate geometry.
void
Mesh::calc_geometry()
{
    #pragma omp parallel for
    for (auto e : all.edges())
    {
        e->calc_geometry();
    }

    #pragma omp parallel for
    for (auto c : all.cells())
    {
        c->calc_geometry();
    }

    // Normal of node can be calcuulated only after
    // normals of all incindent cells.
    #pragma omp parallel for
    for (auto n : all.nodes())
    {
        n->calc_geometry();
    }
}

/// \brief Save geometry.
///
/// Save geometry.
void
Mesh::save_geometry()
{
    #pragma omp parallel for
    for (auto e : all.edges())
    {
        e->save_geometry();
    }

    #pragma omp parallel for
    for (auto c : all.cells())
    {
        c->save_geometry();
    }

    #pragma omp parallel for
    for (auto n : all.nodes())
    {
        n->save_geometry();
    }
}

/// \brief Restore geometry.
///
/// Restore geometry.
void
Mesh::restore_geometry()
{
    #pragma omp parallel for
    for (auto e : all.edges())
    {
        e->restore_geometry();
    }

    #pragma omp parallel for
    for (auto c : all.cells())
    {
        c->restore_geometry();
    }

    #pragma omp parallel for
    for (auto n : all.nodes())
    {
        n->restore_geometry();
    }
}

/// @}

}

}
