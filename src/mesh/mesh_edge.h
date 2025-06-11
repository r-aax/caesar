/// \file
/// \brief Mesh edge declaration.
///
/// Mesh edge declaration.

#ifndef CAESAR_MESH_EDGE_H
#define CAESAR_MESH_EDGE_H

#include "mesh_node.h"
#include "mesh_nodes_holder.h"
#include "mesh_cells_holder.h"
#include "mesh_geometrical.h"
#include "utils/utils.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

class Cell;

/// \brief Mesh edge.
class Edge
    : public utils::DataHolder,
      public utils::IdsHolder,
      public utils::ColorHolder,
      public utils::Markable,
      public NodesHolder,
      public CellsHolder,
      public Geometrical
{

private:

    //
    // Geometry data.
    //

    /// \brief Original length of the edge.
    double original_length_ { 0.0 };

    /// \brief Length of the edge.
    double length_ { 0.0 };

    //
    // Memory leak control.
    //

public:

#ifdef DEBUG
    static int counter;
#endif // DEBUG

    //
    // Constructors/destructors.
    //

    /// \brief Default constructor.
    ///
    /// Default constructor.
    Edge()
    {

#ifdef DEBUG
        ++counter;
#endif // DEBUG

    }

    /// \brief Default destructor.
    ///
    /// Default destructor.
    virtual ~Edge()
    {

#ifdef DEBUG
        --counter;
#endif // DEBUG

    }

    //
    // Print.
    //

    // Print function.
    friend ostream&
    operator<<(ostream& os,
               const Edge& e);

    //
    // Simple properties.
    //

    /// \brief Check if edge is inner.
    ///
    /// Check if edge is inner.
    ///
    /// \return
    /// true - if edge is inner,
    /// false - otherwise.
    inline bool
    is_inner() const
    {
        return cells_count() == 2;
    }

    /// \brief Check if edge is border.
    ///
    /// Check if edge is border.
    ///
    /// \return
    /// true - if edge is border,
    /// false - otherwise.
    inline bool
    is_border() const
    {
        return cells_count() == 1;
    }

    // Check if edge is cross-domain.
    bool
    is_cross() const;

    // Check if edge is domain inner.
    bool
    is_domain_inner() const;

    // Domain of cell 0.
    size_t
    domain_0();

    // Domain of cell 1.
    size_t
    domain_1();

    //
    // Work with geometry.
    //

    /// \brief Get length.
    ///
    /// Get length.
    ///
    /// \return
    /// Length.
    inline double
    length() const
    {
        return length_;
    }

private:

    /// \brief Calculate length.
    ///
    /// Calculate length - distance betweeen two points.
    inline void
    calc_length()
    {
        length_ = node(0)->point().dist_to(node(1)->point());
    }

public:

    /// \brief Calculate geometry.
    ///
    /// Calculate geometry.
    inline void
    calc_geometry()
    {
        calc_length();
    }

    /// \brief Save geometry.
    ///
    /// Save geometry.
    inline void
    save_geometry()
    {
        original_length_ = length_;
    }

    /// \brief Restore geometry.
    ///
    /// Restore geometry.
    inline void
    restore_geometry()
    {
        length_ = original_length_;
    }
};

/// @}

}

}

#endif // !CAESAR_MESH_EDGE_H
