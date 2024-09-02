/// \file
/// \brief Mesh node declaration.
///
/// Mesh node declaration.

#ifndef CAESAR_MESH_NODE_H
#define CAESAR_MESH_NODE_H

#include <vector>
#include <iostream>
#include <iomanip>

#include "mesh_node_element.h"
#include "mesh_cell_element.h"
#include "mesh_edges_holder.h"
#include "mesh_cells_holder.h"
#include "geom/geom.h"
#include "utils/utils.h"

using namespace std;

namespace caesar
{

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
      public utils::Markable,
      public EdgesHolder,
      public CellsHolder
{
    friend class Cell;
    friend class Zone;
    friend class Mesh;
    friend class Remesher;

public:

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

    // Check if node is inner.
    bool
    is_inner() const;

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

    /// \brief Get element from node.
    ///
    /// Get element from node.
    ///
    /// \tparam    TData Type of data.
    /// \param[in] index Index of element.
    ///
    /// \return
    /// Value.
    template<typename TData>
    double
    get_element(int index) const
    {
        NodeElement ne { static_cast<NodeElement>(index) };

        switch (ne)
        {
            case NodeElement::X:
                return point.x;

            case NodeElement::Y:
                return point.y;

            case NodeElement::Z:
                return point.z;

            case NodeElement::NodeMark:
                return get_mark();

            case NodeElement::NodeId:
                return get_id();

            default:
                return get_data<TData>()->get_element(index);
        }
    }

    /// \brief Set data to node.
    ///
    /// Set data to node.
    ///
    /// \tparam    TData Type of data.
    /// \param[in] index Index of element.
    /// \param[in] v     Value.
    template<typename TData>
    void
    set_element(int index,
                double v)
    {
        NodeElement ne { static_cast<NodeElement>(index) };

        switch (ne)
        {
            case NodeElement::X:
                point.x = v;
                break;

            case NodeElement::Y:
                point.y = v;
                break;

            case NodeElement::Z:
                point.z = v;
                break;

            case NodeElement::NodeMark:
                set_mark(static_cast<int>(v));
                break;

            case NodeElement::NodeId:
                DEBUG_ERROR("unable to set node data element " + NodeElementMapper.get_name(ne));
                break;

            default:
                get_data<TData>()->set_element(index, v);
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

    // Calculate ice shift.
    void
    calc_ice_shift();
};

/// @}

}

}

#endif // !CAESAR_MESH_NODE_H
