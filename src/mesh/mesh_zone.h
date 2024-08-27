/// \file
/// \brief Mesh zone declaration.
///
/// Mesh zone declaration.

#ifndef MESH_ZONE_H
#define MESH_ZONE_H

#include "utils/utils.h"
#include "mesh_node.h"
#include "mesh_edge.h"
#include "mesh_cell.h"

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Mesh zone.
class Zone
{
    friend class Mesh;
    friend class Filer;

public:

    /// \brief Name of zone.
    string name { "" };

    /// \brief Count of nodes.
    size_t nodes_count { 0 };

    /// \brief Count of elements.
    size_t elements_count { 0 };

    /// \brief List of points.
    vector<Node*> nodes;

    /// \brief List of edges.
    vector<Edge*> edges;

    /// \brief List of cells.
    vector<Cell*> cells;

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

#endif // MESH_ZONE_H
