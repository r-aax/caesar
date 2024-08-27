/// \file
/// \brief Mesh edge declaration.
///
/// Mesh edge declaration.

#ifndef MESH_EDGE_H
#define MESH_EDGE_H

#include "mesh_node.h"
#include "utils/utils.h"

namespace mesh
{

/// \addtogroup mesh
/// @{

class Cell;

/// \brief Mesh edge.
class Edge
    : public utils::DataHolder,
      public utils::IdsHolder,
      public utils::Markable
{
    friend class Cell;
    friend class Zone;
    friend class Mesh;
    friend class Filer;

private:

    /// \brief Color.
    int color { -1 };

    /// \brief Links to nodes.
    vector<Node*> nodes;

    /// \brief Links to cells.
    vector<Cell*> cells;

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

    /// \brief Get nodes count.
    ///
    /// Get nodes count.
    ///
    /// \return
    /// Nodes count.
    inline size_t
    nodes_count() const
    {
        return nodes.size();
    }

    /// \brief Get cells count.
    ///
    /// Get cells count.
    ///
    /// \return
    /// Cells count.
    inline size_t
    cells_count() const
    {
        return cells.size();
    }

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

    /// \brief Get Node 0.
    ///
    /// Get node 0.
    ///
    /// \return
    /// Node 0.
    inline Node*
    node_0()
    {
        return nodes[0];
    }

    /// \brief Get Node 01
    ///
    /// Get node 1.
    ///
    /// \return
    /// Node 1.
    inline Node*
    node_1()
    {
        return nodes[1];
    }

    // Cell 0.
    Cell*
    cell_0();

    // Cell 1.
    Cell*
    cell_1();

    // Domain of cell 0.
    size_t
    domain_0();

    // Domain of cell 1.
    size_t
    domain_1();

    //
    // Links manipulation.
    //

    /// \brief Add node.
    ///
    /// Add node.
    ///
    /// \param[in] n Node.
    inline void
    add_node(Node* n)
    {
        nodes.push_back(n);
    }

    /// \brief Add cell.
    ///
    /// Add cell.
    ///
    /// \param[in] c Cell.
    inline void
    add_cell(Cell* c)
    {
        cells.push_back(c);
    }

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

#endif // MESH_EDGE_H
