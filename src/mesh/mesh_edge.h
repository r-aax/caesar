/// \file
/// \brief Mesh edge declaration.
///
/// Mesh edge declaration.

#ifndef CAESAR_MESH_EDGE_H
#define CAESAR_MESH_EDGE_H

#include "mesh_node.h"
#include "mesh_nodes_holder.h"
#include "mesh_cells_holder.h"
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
      public utils::Markable,
      public NodesHolder,
      public CellsHolder
{
    friend class Cell;
    friend class Zone;
    friend class Mesh;
    friend class Filer;

private:

    /// \brief Color.
    int color { -1 };

public:

    //
    // Geometry data.
    //

    /// \brief Length of the edge.
    double length { 0.0 };

#ifdef DEBUG
    static int counter;
#endif // DEBUG

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

    // Print function.
    friend ostream&
    operator<<(ostream& os,
               const Edge& e);

    //
    // Some edge flags.
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

    // Domain of cell 0.
    size_t
    domain_0();

    // Domain of cell 1.
    size_t
    domain_1();

    //
    // Data access.
    //

    /// \brief Get color.
    ///
    /// Get color.
    ///
    /// \return
    /// Color.
    inline int
    get_color() const
    {
        return color;
    }

    /// \brief Set color.
    ///
    /// Set color.
    ///
    /// \param[in] color_ Color.
    inline void
    set_color(int color_)
    {
        color = color_;
    }

    //
    // Geometry.
    //

    // Calculate length.
    void
    calc_length();
};

/// @}

}

}

#endif // !CAESAR_MESH_EDGE_H
