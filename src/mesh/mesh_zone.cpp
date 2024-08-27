/// \file
/// \brief Zone implementation.
///
/// Mesh zone implementation.

#include "mesh_zone.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

#ifdef DEBUG
// Counter initialization.
int Zone::counter = 0;
#endif // DEBUG

/// \brief Default constructor.
Zone::Zone()
{

#ifdef DEBUG
    ++counter;
#endif // DEBUG

}

/// \brief Default destructor.
Zone::~Zone()
{

#ifdef DEBUG
    --counter;
#endif // DEBUG

}

/// \brife Print information.
///
/// Print information.
///
/// \param[in] s Stream.
void
Zone::print_info(ostream& s)
{
    s << "Zone name                : " << name << endl;
    s << "Nodes count              : " << nodes_count << endl;
    s << "Elements count           : " << elements_count << endl;
    s << "Nodes vector size        : " << nodes.size() << endl;
    s << "Edges vector size        : " << edges.size() << endl;
    s << "Cells vector size        : " << cells.size() << endl;
    s << ".........................." << endl;
}

/// @}

}

}
