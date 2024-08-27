/// \file
/// \brief Declaration of points cloud.
///
/// Points cloud declaration.

#ifndef GEOM_POINTS_CLOUD_H
#define GEOM_POINTS_CLOUD_H

#include <vector>
#include <string>

#include "geom_vector.h"

using namespace std;

namespace geom
{

/// \addtogroup geom
/// @{

/// \brief Cloud of points.
class PointsCloud
{

private:

    // Data of cloud.
    vector<pair<Vector, double>> d;

public:

    // Default constructor.
    PointsCloud();

    // Connstructor by file.
    PointsCloud(const string& fn);

    // Default destructor.
    ~PointsCloud();

    //
    // Data access.
    //

    // Get data of nearest point.
    double
    get(const Vector& p) const;
};

/// @}

}

#endif // !GEOM_POINTS_CLOUD_H
