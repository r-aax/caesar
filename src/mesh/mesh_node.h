/// \file
/// \brief Mesh node declaration.
///
/// Mesh node declaration.

#ifndef MESH_NODE_H
#define MESH_NODE_H

#include <vector>
#include <iostream>
#include <iomanip>

#include "mesh_node_data_element.h"
#include "mesh_cell_data_element.h"
#include "geom/geom.h"
#include "utils/utils.h"

using namespace std;

namespace mesh
{

/// \addtogroup mesh
/// @{

class Edge;
class Cell;

/// \brief Mesh node.
class Node
    : public utils::DataHolder,
      public utils::IdsHolder,
      public utils::Markable
{
    friend class Cell;
    friend class Zone;
    friend class Mesh;
    friend class Remesher;

public:

    /// \brief Links to edges.
    vector<Edge*> edges;

    /// \brief Links to cells.
    vector<Cell*> cells;

private:

    //
    // Geometry data.
    //

    /// \brief Vector (point).
    geom::Vector point;

    /// \brief Original point.
    ///
    /// Created once while mesh loading
    /// it is impossible to change it.
    const geom::Vector original_point;

    /// \brief Outer normal.
    geom::Vector normal;

    //
    // Tong remesher data.
    //

    /// \brief Ice growing direction.
    geom::Vector ice_dir;

    /// \brief Shift of ice.
    double ice_shift;

    /// \brief Vector shift of node.
    geom::Vector shift;

public:

#ifdef DEBUG
    static int counter;
#endif // DEBUG

    /// \brief Default constructor.
    ///
    /// Default constructor.
    Node()
        : Node(0.0, 0.0, 0.0)
    {
    }

    /// \brief Constructor by point coordinates.
    ///
    /// Constructor by coordinates.
    ///
    /// \param[in] x Point coordinate X.
    /// \param[in] y Point coordinate Y.
    /// \param[in] z Point coordinate Z.
    Node(double x,
         double y,
         double z)
        : point(x, y, z),
          original_point(x, y, z)
    {

#ifdef DEBUG
        ++counter;
#endif // DEBUG

    }

    /// \brief Default destructor.
    ///
    /// Default destructor.
    virtual ~Node()
    {

#ifdef DEBUG
        --counter;
#endif // DEBUG

    }

    // Print function.
    friend ostream&
    operator<<(ostream& os,
               const Node& n);

    /// \brief Get edges count.
    ///
    /// Get edges count.
    ///
    /// \return
    /// Edges count.
    inline size_t
    edges_count() const
    {
        return edges.size();
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

    // Check if node is inner.
    bool
    is_inner() const;

    //
    // Links manupulations.
    //

    /// \brief Add edge.
    ///
    /// Add edge.
    ///
    /// \param[in] e Edge.
    inline void
    add_edge(Edge* e)
    {
        edges.push_back(e);
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

    /// \brief Get point.
    ///
    /// Get point.
    ///
    /// \return
    /// Point.
    inline const geom::Vector&
    get_point() const
    {
        return point;
    }

    /// \brief Get data from node.
    ///
    /// Get data from node.
    ///
    /// \tparam    TData Type of data.
    /// \param[in] index Index of data element.
    ///
    /// \return
    /// Value.
    template<typename TData>
    double
    get_data_element(int index) const
    {
        NodeDataElement nde { static_cast<NodeDataElement>(index) };

        switch (nde)
        {
            case NodeDataElement::X:
                return point.x;

            case NodeDataElement::Y:
                return point.y;

            case NodeDataElement::Z:
                return point.z;

            case NodeDataElement::NodeMark:
                return get_mark();

            case NodeDataElement::NodeId:
                return get_id();

            default:
                return get_data<TData>()->get_data_element(index);
        }
    }

    /// \brief Set data to node.
    ///
    /// Set data to node.
    ///
    /// \tparam    TData Type of data.
    /// \param[in] index Index of data element.
    /// \param[in] v     Value.
    template<typename TData>
    void
    set_data_element(int index,
                     double v)
    {
        NodeDataElement nde { static_cast<NodeDataElement>(index) };

        switch (nde)
        {
            case NodeDataElement::X:
                point.x = v;
                break;

            case NodeDataElement::Y:
                point.y = v;
                break;

            case NodeDataElement::Z:
                point.z = v;
                break;

            case NodeDataElement::NodeMark:
                set_mark(static_cast<int>(v));
                break;

            case NodeDataElement::NodeId:
                DEBUG_ERROR("unable to set node data element " + NodeDataElementMapper.get_name(nde));
                break;

            default:
                get_data<TData>()->set_data_element(index, v);
                break;
        }
    }

    //
    // Geometry.
    //

    /// \brief Restore point from original.
    ///
    /// Restore point from original.
    void
    restore_point()
    {
        point.set(original_point);
    }

    // Calculate outer normal.
    void
    calc_outer_normal();
};

/// @}

}

#endif // MESH_NODE_H
