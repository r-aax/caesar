/// \file
/// \brief Mesh zone declaration.
///
/// Mesh zone declaration.

#ifndef CAESAR_MESH_ZONE_H
#define CAESAR_MESH_ZONE_H

#include "utils/utils.h"
#include "mesh_node.h"
#include "mesh_edge.h"
#include "mesh_cell.h"
#include "mesh_nodes_holder.h"
#include "mesh_edges_holder.h"
#include "mesh_cells_holder.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Mesh zone.
class Zone
    : public NodesHolder,
      public EdgesHolder,
      public CellsHolder
{
    friend class Mesh;
    friend class Filer;

public:

    /// \brief Name of zone.
    string name { "" };

    /// \brief Count of nodes read from file.
    ///
    /// We expect exactly this count of nodes.
    size_t expected_nodes_count { 0 };

    /// \brief Count of elements read from file.
    ///
    /// We expect exactly this count of elements.
    size_t expected_elements_count { 0 };

    /// \brief Heat from anti-icing system (J / (m^2 * s)).
    double q_ais { 0.0 };

public:

#ifdef DEBUG
    static int counter;
#endif // DEBUG

    // Default constructor.
    Zone();

    // Default destructor.
    ~Zone();

    //
    // Data access.
    //

    /// \brief Get heat from anti-icing (J / (m^2 * s)).
    ///
    /// Get heat from anti-icing (J / (m^2 * s)).
    ///
    /// \return
    /// Heat from anti-icing (J / (m^2 * s)).
    inline double
    get_q_ais() const
    {
        return q_ais;
    }

    /// \brief Set heat from anti icing (J / (m^2 * s)).
    ///
    /// Set heat from anti icing (J / (m^2 * s)).
    ///
    /// \param[in] v Value.
    inline void
    set_q_ais(double v)
    {
        q_ais = v;
    }

private:

    // Print information.
    void
    print_info(ostream& s = cout);
};

/// @}

}

}

#endif // !CAESAR_MESH_ZONE_H
