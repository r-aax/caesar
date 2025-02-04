/// \file
/// \brief Mesh files manipulations.
///
/// Mesh files manipulations.

#include "mesh_filer.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Export STL.
///
/// Export STL.
///
/// \param[in] mesh Mesh.
/// \param[in] fn   File name.
void
Filer::export_stl(Mesh& mesh,
                  const string& fn)
{
    size_t cells_count { mesh.all.cells_count() };

    // Open file.
    FILE* fl = fopen(fn.c_str(), "wb");

    // Print header.
    int zero { 0 };
    int header_size { 80 };
    for (int i = 0; i < header_size; ++i)
    {
        fwrite(&zero, 1, 1, fl);
    }

    // Print cells count.
    int32_t cnt { static_cast<int32_t>(mesh.all.cells_count()) };
    fwrite(&cnt, sizeof(cnt), 1, fl);

    // Export all cells.
    for (size_t i = 0; i < cells_count; ++i)
    {
        Cell* c { mesh.all.cell(i) };

        float x1 { static_cast<float>(c->node(0)->point().x) };
        float y1 { static_cast<float>(c->node(0)->point().y) };
        float z1 { static_cast<float>(c->node(0)->point().z) };
        float x2 { static_cast<float>(c->node(1)->point().x) };
        float y2 { static_cast<float>(c->node(1)->point().y) };
        float z2 { static_cast<float>(c->node(1)->point().z) };
        float x3 { static_cast<float>(c->node(2)->point().x) };
        float y3 { static_cast<float>(c->node(2)->point().y) };
        float z3 { static_cast<float>(c->node(2)->point().z) };
        float sub_21_x { x2 - x1 };
        float sub_21_y { y2 - y1 };
        float sub_21_z { z2 - z1 };
        float sub_32_x { x3 - x2 };
        float sub_32_y { y3 - y2 };
        float sub_32_z { z3 - z2 };

        // Compose data.
        float tdata[12];
        tdata[0] = (sub_21_y * sub_32_z - sub_21_z * sub_32_y);
        tdata[1] = (sub_21_z * sub_32_x - sub_21_x * sub_32_z);
        tdata[2] = (sub_21_x * sub_32_y - sub_21_y * sub_32_x);
        tdata[3] = x1;
        tdata[4] = y1;
        tdata[5] = z1;
        tdata[6] = x2;
        tdata[7] = y2;
        tdata[8] = z2;
        tdata[9] = x3;
        tdata[10] = y3;
        tdata[11] = z3;
        char flags[2] = { '\0', '\0' };

        // Write to file.
        fwrite(&tdata[0], 12, 4, fl);
        fwrite(&flags[0], 2, 1, fl);
    }

    fclose(fl);

}

/// \brief Get mesh title from string.
///
/// Get title from string.
///
/// \param[in,out] mesh Mesh.
/// \param[in]     s    String.
void
Filer::get_mesh_title_from_string(Mesh& mesh,
                                  const string& s)
{
    size_t p { 0 };
    size_t len { 0 };

    if (!utils::find_substr_in_double_quotes(s, 0, p, len))
    {
        DEBUG_ERROR("no title is found while loading the mesh");
    }

    mesh.title = s.substr(p, len);
}

/// \brief Get mesh variables names from string.
///
/// Get variables names from string.
///
/// \param[in,out] mesh Mesh.
/// \param[in]     s    String.
void
Filer::get_mesh_variables_names_from_string(Mesh& mesh,
                                            const string& s)
{
    size_t p { 0 };
    size_t len { 0 };

    // Clear names.
    mesh.variables_names.clear();

    while (utils::find_substr_in_double_quotes(s, p, p, len))
    {
        mesh.variables_names.push_back(s.substr(p, len));
        p += (len + 1);
    }

    // We suppose that first 3 elements of data are X, Y, Z xoordinates of nodes.
    DEBUG_CHECK_ERROR((mesh.variables_names[0] == "X")
                      && (mesh.variables_names[1] == "Y")
                      && (mesh.variables_names[2] == "Z"),
                      "first 3 elements of data are not X, Y, Z");
}

/// \brief Store mesh variables names.
///
/// \param[in] variables_names List of variables names to store.
/// \param[in] f               File stream.
void
Filer::store_mesh_variables_names(const vector<string>& variables_names,
                                  ofstream& f)
{
    size_t n = variables_names.size();

    f << "VARIABLES=";

    for (size_t i = 0; i < n; ++i)
    {
        f << "\"" << variables_names[i] << "\"";

        if (i < n - 1)
        {
            f << ", ";
        }
    }

    f << endl;
}

/// \brief Get zone name from string.
///
/// Get name frm string.
///
/// \param[in,out] zone Zone.
/// \param[in]     s    String.
void
Filer::get_zone_name_from_string(Zone* zone,
                                 const string& s)
{
    size_t p { 0 };
    size_t len { 0 };

    if (!utils::find_substr_in_double_quotes(s, 0, p, len))
    {
        DEBUG_ERROR("no zone name is found in the string");
    }

    zone->name = s.substr(p, len);
}

/// \brief Get zone nodes count from string.
///
/// Get nodes count from string.
///
/// \param[in,out] zone Zone.
/// \param[in]     s    String.
void
Filer::get_zone_nodes_count_from_string(Zone* zone,
                                        const string& s)
{
    zone->expected_nodes_count = static_cast<size_t>(utils::get_int_from_str_after_eq_sign(s));
}

/// \brief Get zone elements count from string.
///
/// Get elements count from string.
///
/// \param[in,out] zone Zone.
/// \param[in]     s    String.
void
Filer::get_zone_elements_count_from_string(Zone* zone,
                                           const string& s)
{
    zone->expected_elements_count = static_cast<size_t>(utils::get_int_from_str_after_eq_sign(s));
}

/// \brief Get zone varlocation from string.
///
/// Get zone varlocation cellcentered from string.
///
/// \param[in,out] mesh Mesh.
/// \param[in]     s    String.
void
Filer::get_zone_varlocation_cellcentered_from_string(Mesh& mesh,
                                                     const string& s)
{
    size_t lo, hi;

    if (!utils::find_interval_int_bounds_in_str(s, lo, hi))
    {
        DEBUG_ERROR("no varlocation cellcentered variables are found in the string");
    }

    if (mesh.varlocation_cellcentered.first == 0)
    {
        mesh.varlocation_cellcentered.first = lo;
        mesh.varlocation_cellcentered.second = hi;
    }
    else
    {
        DEBUG_CHECK_ERROR((mesh.varlocation_cellcentered.first == lo)
                          && (mesh.varlocation_cellcentered.second == hi),
                          "variables varlocation for different zones are not equal ("
                          + to_string(mesh.varlocation_cellcentered.first) + ", "
                          + to_string(mesh.varlocation_cellcentered.second)
                          + ") != (" + to_string(lo) + ", " + to_string(hi) + ")");
    }
}

/// \brief Get zone data from string.
///
/// Get data from string.
///
/// \param[in,out] data Data.
/// \param[in]     s    String.
void
Filer::get_zone_data_from_string(vector<vector<double>>& data,
                                 const string& s)
{
    size_t p { 0 };
    size_t len { 0 };
    vector<double> data_line;

    while (utils::find_word(s, p, p, len))
    {
        data_line.push_back(stod(s.substr(p, len)));
        p += (len + 1);
    }

    data.push_back(data_line);
}

/// \brief Link node and edge.
///
/// Link node and edge.
///
/// \param[in,out] n Node.
/// \param[in,out] e Edge.
void
Filer::link_node_edge(Node* n,
                      Edge* e)
{
    n->add_edge(e);
    e->add_node(n);
}

/// \brief Link node and cell.
///
/// Link node and cell.
///
/// \param[in,out] n Node.
/// \param[in,out] c Cell.
void
Filer::link_node_cell(Node* n,
                      Cell* c)
{
    n->add_cell(c);
    c->add_node(n);
}

/// \brief Link edge and cell.
///
/// Link edge and cell.
///
/// \param[in,out] e Edge.
/// \param[in,out] c Cell.
void
Filer::link_edge_cell(Edge* e,
                      Cell* c)
{
    e->add_cell(c);
    c->add_edge(e);
}

/// \brief Store zone links.
///
/// \param[in] zone Zone.
/// \param[in] f    File stream.
void
Filer::store_zone_links(Zone* zone,
                        ofstream& f)
{
    // Set local identifiers to marks.
    for (size_t i = 0; i < zone->nodes_count(); ++i)
    {
        zone->node(i)->set_mark(static_cast<int>(i));
    }

    // Store links.
    for (size_t i = 0; i < zone->cells_count(); ++i)
    {
        f << (zone->cell(i)->node(0)->get_mark() + 1) << " "
          << (zone->cell(i)->node(1)->get_mark() + 1) << " "
          << (zone->cell(i)->node(2)->get_mark() + 1) << endl;
    }
}

/// @}

}

}
