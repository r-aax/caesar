/// \file
/// \brief Mesh cell declaration.
///
/// Mesh cell declaration.

#ifndef MESH_CELL_H
#define MESH_CELL_H

#include "mesh_edge.h"

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Mesh cell.
class Cell
{
    friend class Zone;

private:

    /// \brief Identifier.
    int id { -1 };

    /// \brief Links to nodes.
    vector<shared_ptr<Node>> nodes;

    /// \brief Links to edges.
    vector<shared_ptr<Edge>> edges;

    //
    // Solver data.
    //

    /// \brief Temperature (C).
    double t { 0.0 };

    /// \brief Height of water (m).
    double hw { 0.0 };

    /// \brief Height of ice (m).
    double hi { 0.0 };

    /// \brief Heat transfer coefficient.
    double htc { 0.0 };

    /// \brief Coefficient of water catching.
    double beta { 0.0 };

    /// \brief Tau X coordinate.
    double tau_x { 0.0 };

    /// \brief Tau Y coordinate.
    double tau_y { 0.0 };

    /// \brief Tau Z coordinate.
    double tau_z { 0.0 };

public:

#ifdef DEBUG
    static int counter;
#endif // DEBUG

    // Default constructor.
    Cell();

    // Default destructor.
    virtual
    ~Cell();

    // Print function.
    friend ostream&
    operator<<(ostream& os,
               const Cell& c);
};

/// @}

}

#endif // MESH_CELL_H
