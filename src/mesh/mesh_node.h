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

private:

    //
    // Geometry data.
    // Node has geometry data of two types: original and current.
    //

    /// \brief Original point.
    ///
    /// Original point, set once while loading.
    geom::Vector original_point_;

    /// \brief Current point.
    ///
    /// Current point.
    geom::Vector point_;

    /// \brief Original normal.
    ///
    /// Original normal, set once while loading.
    geom::Vector original_normal_;

    /// \brief Current normal.
    ///
    /// Current normal.
    geom::Vector normal_;

public:

    //
    // Remesher data.
    //

    /// \brief Ice growing direction.
    geom::Vector ice_dir;

    /// \brief Shift of ice.
    double ice_shift;

    /// \brief Vector shift of node.
    geom::Vector shift;

    //
    // Memory leak control.
    //

#ifdef DEBUG
    static int counter;
#endif // DEBUG

    //
    // Constructors/destructors.
    //

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
        : original_point_(x, y, z),
          point_(x, y, z)
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

    //
    // Print.
    //

    // Print function.
    friend ostream&
    operator<<(ostream& os,
               const Node& n);

    //
    // Simple properties.
    //

    // Check if node is inner.
    bool
    is_inner() const;

    //
    // Work with geometry.
    //

    /// \brief Get original point.
    ///
    /// Original point.
    ///
    /// \return
    /// Original point.
    inline const geom::Vector&
    original_point() const
    {
        return original_point_;
    }

    /// \brief Get point.
    ///
    /// Point.
    ///
    /// \return
    /// Point.
    inline const geom::Vector&
    point() const
    {
        return point_;
    }

    /// \brief Get origina normal.
    ///
    /// Get original normal.
    ///
    /// \return
    /// Original normal.
    inline const geom::Vector&
    original_normal() const
    {
        return original_normal_;
    }

    /// \brief Get normal.
    ///
    /// Get normal.
    ///
    /// \return
    /// Normal.
    inline const geom::Vector&
    normal() const
    {
        return normal_;
    }

    /// \brief Move point.
    ///
    /// Move point.
    ///
    /// \param[in] v Vector.
    inline void
    move(const geom::Vector& v)
    {
        point_.add(v);
    }

    // Calculate normal.
    void
    calc_normal();

    /// \brief Calculate geometry.
    ///
    /// Calculate geometry.
    inline void
    calc_geometry()
    {
        calc_normal();
    }

    /// \brief Save geometry.
    ///
    /// Save geometry.
    inline void
    save_geometry()
    {
        original_point_.set(point_);
        original_normal_.set(normal_);
    }

    /// \brief Restore geometry.
    ///
    /// Restore geometry.
    inline void
    restore_geometry()
    {
        point_.set(original_point_);
        normal_.set(original_normal_);
    }

    //
    // Work with remesh data.
    //

    // Calculate ice shift.
    void
    calc_ice_shift();

    //
    // Data access.
    //

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
                return point_.x;

            case NodeElement::Y:
                return point_.y;

            case NodeElement::Z:
                return point_.z;

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
                point_.x = v;
                break;

            case NodeElement::Y:
                point_.y = v;
                break;

            case NodeElement::Z:
                point_.z = v;
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
};

/// @}

}

}

#endif // !CAESAR_MESH_NODE_H
