/// \file
/// \brief Declaration of points cloud.
///
/// Points cloud declaration.

#ifndef CAESAR_GEOM_POINTS_CLOUD_H
#define CAESAR_GEOM_POINTS_CLOUD_H

#include <vector>
#include <string>

#include "geom_vector.h"

using namespace std;

namespace caesar
{

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

}

#endif // !CAESAR_GEOM_POINTS_CLOUD_H
