/// \file
/// \brief Zone implementation.
///
/// Mesh zone implementation.

#include "mesh_zone.h"

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Default constructor.
Zone::Zone()
{
}

/// \brief Default destructor.
Zone::~Zone()
{
}

/// \brief Get name from string.
///
/// Get name frm string.
///
/// \param[in] s String.
void
Zone::get_name_from_string(const string& s)
{
    int p, len;

    if (!utils::find_substr_in_double_quotes(s, 0, p, len))
    {
        DEBUG_ERROR("no zone name is found in the string");
    }

    name = s.substr(p, len);
}

/// \brief Get nodes count from string.
///
/// Get nodes count from string.
///
/// \param[in] s String.
void
Zone::get_nodes_count_from_string(const string& s)
{
    nodes_count = utils::get_int_from_str_after_eq_sign(s);
}

/// \brief Get elements count from string.
///
/// Get elements count from string.
///
/// \param[in] s String.
void
Zone::get_elements_count_from_string(const string& s)
{
    elements_count = utils::get_int_from_str_after_eq_sign(s);
}

/// \brief Get varlocation from string.
///
/// Get varlocation cellcentered from string.
///
/// \param[in] s String.
void
Zone::get_varlocation_cellcentered_from_string(const string& s)
{
    int lo, hi;

    if (!utils::find_interval_int_bounds_in_str(s, lo, hi))
    {
        DEBUG_ERROR("no varlocation cellcentered variables are found in the string");
    }

    varlocation_cellcentered.first = lo;
    varlocation_cellcentered.second = hi;
}

/// \brief Get data from string.
///
/// Get data from string.
///
/// \param[in] s String.
void
Zone::get_data_from_string(const string& s)
{
    int p { -1 }, len { 0 };
    vector<double> data_line;

    while (utils::find_word(s, p + len + 1, p, len))
    {
        data_line.push_back(stod(s.substr(p, len)));
    }

    data.push_back(data_line);
}

/// \brief Get links from string.
///
/// Get links from string.
///
/// \param[in] s          String.
/// \param[in] cell_index Cell index.
void
Zone::get_links_from_string(const string& s,
                            int cell_index)
{
    int p { -1 }, len { 0 };
    vector<int> links;

    while (utils::find_word(s, p + len + 1, p, len))
    {
        links.push_back(stoi(s.substr(p, len)));
    }

    // Links has 3 integers.
    DEBUG_CHECK(links.size() == 3, "wrong element-node link line");

    // Set links between cells and nodes.
    for (int i = 0; i < links.size(); ++i)
    {
        cells[cell_index]->nodes.push_back(nodes[links[i] - 1]);
    }
}

/// \brief Store data.
///
/// \param[in] f File stream.
void
Zone::store_data(ofstream& f)
{
    auto n = data.size();

    f.precision(17);

    for (int i = 0; i < n; ++i)
    {
        auto m = data[i].size();

        for (int j = 0; j < m; ++j)
        {
            f << data[i][j];

            if (j < m - 1)
            {
                f << " ";
            }
        }

        f << endl;
    }
}

/// \brief Store links.
///
/// \param[in] f File stream.
void
Zone::store_links(ofstream& f)
{
    // Set local identifiers to marks.
    for (int i = 0; i < nodes.size(); ++i)
    {
        nodes[i]->mark = i;
    }

    // Store links.
    for (int i = 0; i < cells.size(); ++i)
    {
        f << (cells[i]->nodes[0]->mark + 1) << " "
          << (cells[i]->nodes[1]->mark + 1) << " "
          << (cells[i]->nodes[2]->mark + 1) << endl;
    }
}

/// \brife Print information.
///
/// Print information.
///
/// \param[in] s                 Stream.
/// \param[in] is_print_elements Flag for printing nodes/edges/cells.
void
Zone::print_info(ostream& s,
                 bool is_print_elements)
{
    s << "    Zone name                : " << name << endl;
    s << "    Nodes count              : " << nodes_count << endl;
    s << "    Elements count           : " << elements_count << endl;
    s << "    Varlocation cellcentered : "
      << varlocation_cellcentered.first << " " << varlocation_cellcentered.second << endl;
    s << "    Nodes vector size        : " << nodes.size() << endl;
    s << "    Edges vector size        : " << edges.size() << endl;
    s << "    Cells vector size        : " << cells.size() << endl;


    if (is_print_elements)
    {
        s << "    Nodes:" << endl;

        for (auto n : nodes)
        {
            s << "      " << (*n) << endl;
        }

        s << "    Edges:" << endl;

        for (auto e : edges)
        {
            s << "      " << (*e) << endl;
        }

        s << "    Cells:" << endl;

        for (auto c : cells)
        {
            s << "      " << (*c) << endl;
        }
    }

    s << "    --------" << endl;
}

/// \brief Build.
///
/// Build zone nodes and cells.
void
Zone::build_nodes_and_cells()
{
    // First 3 elements of data are X, Y, Z - so build nodes from them.
    // These 3 elements of data must be of size nodes_count.
    DEBUG_CHECK(data[0].size() == nodes_count, "wrong size of nodes X array");
    DEBUG_CHECK(data[1].size() == nodes_count, "wrong size of nodes Y array");
    DEBUG_CHECK(data[2].size() == nodes_count, "wrong size of nodes Z array");

    // Build nodes.
    for (int i = 0; i < nodes_count; ++i)
    {
        nodes.push_back(make_shared<Node>(data[0][i], data[1][i], data[2][i]));
    }

    // Check size of data for cells.
    for (int i = 3; i < data.size(); ++i)
    {
        DEBUG_CHECK(data[i].size() == elements_count, "wrong size of cells data array");
    }

    // Build cells.
    for (int i = 0; i < elements_count; ++i)
    {
        cells.push_back(make_shared<Cell>());
    }
}

/// @}

}
