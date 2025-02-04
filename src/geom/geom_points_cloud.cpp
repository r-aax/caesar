/// \file
/// \brief Points cloud implementation.
///
/// Points cloud implementation.

#include "geom_points_cloud.h"

#include <iostream>
#include <fstream>

namespace caesar
{

namespace geom
{

/// \addtogroup geom
/// @{

/// \brief Default constructor.
///
/// Default constructor.
PointsCloud::PointsCloud()
{
}

/// \brief Connstructor by file.
///
/// Constructor by file.
///
/// \param[in] fn Name of file.
PointsCloud::PointsCloud(const string& fn)
{
    ifstream f(fn);

    if (!f.is_open())
    {
        DEBUG_ERROR("no file " + fn + " found");
    }

    string line { "" };
    vector<string> ws;

    // Read all lines of the file.
    while (getline(f, line))
    {
        utils::split_into_words(line, ",", ws);

        if (ws.size() == 4)
        {
            try
            {
                d.push_back(pair<Vector, double> { Vector(stod(ws[0]), stod(ws[1]), stod(ws[2])),
                                                   stod(ws[3]) });
            }
            catch (...)
            {
                ;
            }
        }
    }

    f.close();
}

/// \brief Default destructor.
///
/// Default destructor.
PointsCloud::~PointsCloud()
{
}

//
// Data access.
//

/// \brief Get data of nearest point.
///
/// Get data of nearest point.
///
/// \param[in] p Point.
///
/// \return
/// Data of nearest point.
double
PointsCloud::get(const Vector& p) const
{
    size_t n { d.size() };
    double min_dist { numeric_limits<double>::infinity() };
    double val { 0.0 };

    // Not efficient linear approach to find nearest point.
    for (size_t i = 0; i < n; ++i)
    {
        const pair<Vector, double>& x { d[i] };
        double dist { x.first.dist_to(p) };

        if (dist < min_dist)
        {
            min_dist = dist;
            val = x.second;
        }
    }

    return val;
}

/// @}

}

}
