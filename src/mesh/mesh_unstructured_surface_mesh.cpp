/// \file
/// \brief Unstructured surface mesh implementation.
///
/// Implementation of unstructured surface mesh.

#include "mesh_unstructured_surface_mesh.h"

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Default constructor.
UnstructuredSurfaceMesh::UnstructuredSurfaceMesh()
{
}

/// \brief Default destructor.
UnstructuredSurfaceMesh::~UnstructuredSurfaceMesh()
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
UnstructuredSurfaceMesh::load(const string& fn)
{
    ifstream f(fn);
    string line;
    shared_ptr<Zone> current_zone;

    if (!f.is_open())
    {
        return false;
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

            int p, len;

            if (!utils::find_substr_in_double_quotes(line, 0, p, len))
            {
                DEBUG_ERROR("no title is found while loading the mesh");
            }

            title = line.substr(p, len);
        }
        else if (line.starts_with("VARIABLES="))
        {
            // Get variables names.

            int p { -1 }, len { 0 };

            // Clear names.
            variables_names.clear();

            while (utils::find_substr_in_double_quotes(line, p + len + 1, p, len))
            {
                variables_names.push_back(line.substr(p, len));
            }
        }
        else if (line.starts_with("ZONE T="))
        {
            // Get zone name.

            // It is the time for us to create new zone.
            zones.push_back(make_shared<Zone>());
            current_zone = zones.back();

            int p, len;

            if (!utils::find_substr_in_double_quotes(line, 0, p, len))
            {
                DEBUG_ERROR("no zone name is found while loading the mesh");
            }

            current_zone->name = line.substr(p, len);
        }
        else if (line.starts_with("NODES="))
        {
            // Get nodes count.

            current_zone->nodes_count = utils::get_int_from_str_after_eq_sign(line);
        }
        else if (line.starts_with("ELEMENTS="))
        {
            // Get elements count.

            current_zone->elements_count = utils::get_int_from_str_after_eq_sign(line);
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

            int lo, hi;

            if (!utils::find_interval_int_bounds_in_str(line, lo, hi))
            {
                DEBUG_ERROR("no varlocation cellcentered variables are found while loading the mesh");
            }

            current_zone->varlocation_cellcentered.first = lo;
            current_zone->varlocation_cellcentered.second = hi;
        }
        else if (current_zone->data.size() < variables_names.size())
        {
            // Read data line.

            int p { -1 }, len { 0 };
            vector<double> data_line;

            while (utils::find_word(line, p + len + 1, p, len))
            {
                data_line.push_back(stod(line.substr(p, len)));
            }

            current_zone->data.push_back(data_line);
        }
        else if (current_zone->links.size() < current_zone->elements_count)
        {
            // Read links.

            int p { -1 }, len { 0 };
            vector<int> links_line;

            while (utils::find_word(line, p + len + 1, p, len))
            {
                links_line.push_back(stoi(line.substr(p, len)));
            }

            current_zone->links.push_back(links_line);

            // Check for end of zone.
            if (current_zone->links.size() == current_zone->elements_count)
            {
                cout << "end of zone" << endl;
            }
        }
    }

    cout << zones.size() << endl;

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
UnstructuredSurfaceMesh::store(const string& fn)
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

/// \brief Store variables names.
///
/// \param[in] f File stream.
void
UnstructuredSurfaceMesh::store_variables_names(ofstream& f)
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
