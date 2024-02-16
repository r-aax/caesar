/// \file
/// \brief Unstructured surface mesh implementation.
///
/// Implementation of unstructured surface mesh.

#include "mesh_mesh.h"

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Default constructor.
Mesh::Mesh()
{
}

/// \brief Default destructor.
Mesh::~Mesh()
{
}

/// \brief Load mesh.
///
/// Load mesh from file.
///
/// A list of supported files:
/// - *.dat file.
///
/// \param[in] fn Name of file.
///
/// \return
/// true - if mesh is loaded successfully,
/// false - otherwise.
bool
Mesh::load(const string& fn)
{
    ifstream f(fn);
    string line;
    shared_ptr<Zone> current_zone;

    if (!f.is_open())
    {
        return false;
    }

    // We do not load meshes more than one time.
    if (zones.size() > 0)
    {
        DEBUG_ERROR("repeated mesh loading");
    }

    while (getline(f, line))
    {
        if (line.empty())
        {
            // Ignore empty line.
            ;
        }
        else if (line[0] == '#')
        {
            // Ignore comment line.
            ;
        }
        else if (line.starts_with("TITLE="))
        {
            // Get title.
            get_title_from_string(line);
        }
        else if (line.starts_with("VARIABLES="))
        {
            // Get variables names.
            get_variables_names_from_string(line);

            // We suppose that first 3 elements of data are X, Y, Z xoordinates of nodes.
            DEBUG_CHECK((variables_names[0] == "X")
                        && (variables_names[1] == "Y")
                        && (variables_names[2] == "Z"),
                        "first 3 elements of data are not X, Y, Z");
        }
        else if (line.starts_with("ZONE T="))
        {
            // Get zone name.

            // It is the time for us to create new zone.
            zones.push_back(make_shared<Zone>());
            current_zone = zones.back();

            // Get its name.
            current_zone->get_name_from_string(line);
        }
        else if (line.starts_with("NODES="))
        {
            // Get nodes count.
            current_zone->get_nodes_count_from_string(line);
        }
        else if (line.starts_with("ELEMENTS="))
        {
            // Get elements count.
            current_zone->get_elements_count_from_string(line);
        }
        else if (line.starts_with("DATAPACKING="))
        {
            // Get datapacking type.
            // Now only BLOCK is supported.
            ;
        }
        else if (line.starts_with("ZONETYPE="))
        {
            // Get zone type.
            // Now only FETRIANGLE is supported.
            ;
        }
        else if (line.starts_with("VARLOCATION="))
        {
            // Get varlocation.
            current_zone->get_varlocation_cellcentered_from_string(line);
        }
        else
        {
            // First line of data.
            current_zone->get_data_from_string(line);

            // Rest lines of data.
            for (int i = 1; i < variables_names.size(); ++i)
            {
                getline(f, line);
                current_zone->get_data_from_string(line);
            }

            // Allocate memory for nodes and cells.
            current_zone->build_nodes_and_cells();

            // Links.
            for (int i = 0; i < current_zone->elements_count; ++i)
            {
                getline(f, line);
                current_zone->get_links_from_string(line, i);
            }
        }
    }

    f.close();

    return true;
}

/// \brief Store mesh.
///
/// Store mesh to file.
///
/// \param[in] fn Name of file.
///
/// \return
/// true - if store is complete successfully,
/// false - otherwise.
bool
Mesh::store(const string& fn)
{
    ofstream f(fn);

    if (!f.is_open())
    {
        return false;
    }

    // First line is comment with name of program.
    f << "# CAEsar export" << endl;

    // Title line.
    f << "TITLE=\"" << title << "\"" << endl;

    // Variables line.
    store_variables_names(f);

    // Store all zones.
    for (int i = 0; i < zones.size(); ++i)
    {
        shared_ptr<Zone> current_zone = zones[i];

        // Zone name line.
        f << "ZONE T=\"" << current_zone->name << "\"" << endl;

        // Nodes count line.
        f << "NODES=" << current_zone->nodes_count << endl;

        // Elements count line.
        f << "ELEMENTS=" << current_zone->elements_count << endl;

        // Datapacking line.
        f << "DATAPACKING=BLOCK" << endl;

        // Zone type line.
        f << "ZONETYPE=FETRIANGLE" << endl;

        // Varlocation line.
        f << "VARLOCATION=(["
          << current_zone->varlocation_cellcentered.first << "-"
          << current_zone->varlocation_cellcentered.second << "]=CELLCENTERED)" << endl;

        // Store all data.
        current_zone->store_data(f);

        // Store links.
        current_zone->store_links(f);
    }

    f.close();

    return true;
}

/// \brief Print information.
///
/// Print information.
///
/// \param[in] f                 Stream.
/// \param[in] is_print_elements Flag for printing nodes/edges/cells.
void
Mesh::print_info(ostream& s,
                 bool is_print_elements)
{
    s << "UnstructuredSurfaceMesh" << endl;
    s << "Title           : " << title << endl;
    s << "Variables names :";

    for (auto& vn : variables_names)
    {
        s << " \"" << vn << "\"";
    }

    s << endl;
    s << "Zones count     : " << zones.size() << endl;

    for (auto& zone : zones)
    {
        zone->print_info(s, is_print_elements);
    }
}

/// \brief Get title from string.
///
/// Get title from string.
///
/// \param[in] s String.
void
Mesh::get_title_from_string(const string& s)
{
    int p, len;

    if (!utils::find_substr_in_double_quotes(s, 0, p, len))
    {
        DEBUG_ERROR("no title is found while loading the mesh");
    }

    title = s.substr(p, len);
}

/// \brief Get variables names from string.
///
/// Get variables names from string.
///
/// \param[in] s String.
void
Mesh::get_variables_names_from_string(const string& s)
{
    int p { -1 }, len { 0 };

    // Clear names.
    variables_names.clear();

    while (utils::find_substr_in_double_quotes(s, p + len + 1, p, len))
    {
        variables_names.push_back(s.substr(p, len));
    }
}

/// \brief Store variables names.
///
/// \param[in] f File stream.
void
Mesh::store_variables_names(ofstream& f)
{
    auto n = variables_names.size();

    f << "VARIABLES=";

    for (int i = 0; i < n; ++i)
    {
        f << "\"" << variables_names[i] << "\"";

        if (i < n - 1)
        {
            f << ", ";
        }
    }

    f << endl;
}

/// @}

}
