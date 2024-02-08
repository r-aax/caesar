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

    if (!f.is_open())
    {
        return false;
    }

    // Clear data.
    data.clear();

    // Clear links.
    links.clear();

    string line;

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
                cout << "ERROR" << endl;
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

            int p, len;

            if (!utils::find_substr_in_double_quotes(line, 0, p, len))
            {
                cout << "ERROR" << endl;
            }

            zone_name = line.substr(p, len);
        }
        else if (line.starts_with("NODES="))
        {
            // Get nodes count.

            nodes_count = utils::get_int_from_str_after_eq_sign(line);
        }
        else if (line.starts_with("ELEMENTS="))
        {
            // Get elements count.

            elements_count = utils::get_int_from_str_after_eq_sign(line);
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
                cout << "ERROR" << endl;
            }

            varlocation_cellcentered.first = lo;
            varlocation_cellcentered.second = hi;
        }
        else if (data.size() < variables_names.size())
        {
            // Read data line.

            int p { -1 }, len { 0 };
            vector<double> data_line;

            while (utils::find_word(line, p + len + 1, p, len))
            {
                data_line.push_back(stod(line.substr(p, len)));
            }

            data.push_back(data_line);
        }
        else if (links.size() < elements_count)
        {
            // Read links.

            int p { -1 }, len { 0 };
            vector<int> links_line;

            while (utils::find_word(line, p + len + 1, p, len))
            {
                links_line.push_back(stoi(line.substr(p, len)));
            }

            links.push_back(links_line);

            // Check for end of zone.
            if (links.size() == elements_count)
            {
                cout << "end of zone" << endl;
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

    // Zone name line.
    f << "ZONE T=\"" << zone_name << "\"" << endl;

    // Nodes count line.
    f << "NODES=" << nodes_count << endl;

    // Elements count line.
    f << "ELEMENTS=" << elements_count << endl;

    // Datapacking line.
    f << "DATAPACKING=BLOCK" << endl;

    // Zone type line.
    f << "ZONETYPE=FETRIANGLE" << endl;

    // Varlocation line.
    f << "VARLOCATION=(["
      << varlocation_cellcentered.first << "-"
      << varlocation_cellcentered.second << "]=CELLCENTERED)" << endl;

    // Store all data.
    store_data(f);

    // Store links.
    store_links(f);

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

/// \brief Store data.
///
/// \param[in] f File stream.
void
UnstructuredSurfaceMesh::store_data(ofstream& f)
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
UnstructuredSurfaceMesh::store_links(ofstream& f)
{
    auto n = links.size();

    for (int i = 0; i < n; ++i)
    {
        auto m = links[i].size();

        for (int j = 0; j < m; ++j)
        {
            f << links[i][j];

            if (j < m - 1)
            {
                f << " ";
            }
        }

        f << endl;
    }
}

/// @}

}
