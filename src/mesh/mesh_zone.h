/// \file
/// \brief Mesh zone declaration.
///
/// Mesh zone declaration.

#ifndef MESH_ZONE_H
#define MESH_ZONE_H

#include "utils/utils.h"
#include "mesh_node.h"
#include "mesh_edge.h"
#include "mesh_cell.h"

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Mesh zone.
class Zone
{
    friend class Mesh;

private:

    /// \brief Name of zone.
    string name { "" };

    /// \brief Count of nodes.
    int nodes_count { 0 };

    /// \brief Count of elements.
    int elements_count { 0 };

    /// \brief Varlocation cellcentered variables.
    pair<int, int> varlocation_cellcentered;

    /// \brief Loaded data.
    vector<vector<double>> data;

    /// \brief List of points.
    vector<shared_ptr<Node>> nodes;

    /// \brief List of edges.
    vector<shared_ptr<Edge>> edges;

    /// \brief List of cells.
    vector<shared_ptr<Cell>> cells;

public:

    // Default constructor.
    Zone();

    // Default destructor.
    ~Zone();

private:

    // Get name from string.
    void
    get_name_from_string(const string& s);

    // Get nodes count from string.
    void
    get_nodes_count_from_string(const string& s);

    // Get elements count from string.
    void
    get_elements_count_from_string(const string& s);

    // Get varlocation from string.
    void
    get_varlocation_cellcentered_from_string(const string& s);

    // Get data from string.
    void
    get_data_from_string(const string& s);

    // Get links from string.
    void
    get_links_from_string(const string& s,
                          int cell_index);

    // Store data.
    void
    store_data(ofstream& f,
               vector<string>& variables_names);

    // Store links.
    void
    store_links(ofstream& f);

    // Print information.
    void
    print_info(ostream& s = cout,
               bool is_print_elements = false);

    // Build.
    void
    build_nodes_and_cells(vector<string> variables_names);
};

/// @}

}

#endif // MESH_ZONE_H
