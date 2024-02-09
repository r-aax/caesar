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
