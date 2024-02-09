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
/// \param[in] s String.
void
Zone::get_links_from_string(const string& s)
{
    int p { -1 }, len { 0 };
    vector<int> links_line;

    while (utils::find_word(s, p + len + 1, p, len))
    {
        links_line.push_back(stoi(s.substr(p, len)));
    }

    links.push_back(links_line);
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
