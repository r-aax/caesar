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
Zone::print_info(ostream& s) const
{
    s << "Zone name                : " << name << endl;
    s << "Nodes count              : " << expected_nodes_count << endl;
    s << "Elements count           : " << expected_elements_count << endl;
    s << "Nodes vector size        : " << nodes_count() << endl;
    s << "Edges vector size        : " << edges_count() << endl;
    s << "Cells vector size        : " << cells_count() << endl;
    s << ".........................." << endl;
}

/// @}

}

}
