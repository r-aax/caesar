/// \file
/// \brief Mesh cell declaration.
///
/// Mesh cell declaration.

#ifndef CAESAR_MESH_CELL_H
#define CAESAR_MESH_CELL_H

#include "mesh_cell_data_element.h"
#include "mesh_edge.h"
#include "mesh_nodes_holder.h"
#include "mesh_edges_holder.h"
#include "geom/geom.h"
#include "phys/phys.h"
#include "utils/utils.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

class Zone;

/// \brief Mesh cell.
class Cell
    : public utils::DataHolder,
      public utils::IdsHolder,
      public utils::Markable,
      public NodesHolder,
      public EdgesHolder
{
    friend class Node;
    friend class Edge;
    friend class Zone;
    friend class Mesh;
    friend class Filer;
    friend class Remesher;
    friend class Decomposer;

private:

    /// \brief Domain number.
    ///
    /// By default there is only one domain with number zero.
    size_t domain { 0 };

public:

    /// \brief Fictitious points.
    ///
    /// Use fictitious points define fictitious orientaton of the cell.
    vector<geom::Vector> fictitious_points;

private:

    /// \brief Zone.
    Zone* zone { nullptr };

    /// \brief Links to neighbourhood.
    vector<Cell*> neighbourhood;

    //
    // Geometry data.
    //

    /// \brief Area.
    double area { 0.0 };

    /// \brief Saved area.
    double saved_area { 0.0 };

    /// \brief Center vector.
    geom::Vector center;

    /// \brief Outer normal.
    geom::Vector normal;

public:

    /// \brief Fictitious outer normal.
    geom::Vector fictitious_normal;

public:

    //
    // Remesher data.
    //

    /// \brief Ice volume we want to grow (m^3).
    double target_ice { 0.0 };

    /// \brief Ice volume rest to grow (m^3).
    double rest_ice { 0.0 };

    /// \brief Remesh ice chunk (m^3).
    double ice_chunk { 0.0 };

    /// \brief Local ice chunk for redistributing (m^3).
    double loc_ice_chunk { 0.0 };

    /// \brief Ice growing direction.
    geom::Vector ice_dir;

    /// \brief Ice shift (m).
    double ice_shift { 0.0 };

public:

#ifdef DEBUG
    static int counter;
#endif // DEBUG

    /// \brief Default constructor.
    ///
    /// Default constructor.
    Cell()
    {

#ifdef DEBUG
        ++counter;
#endif // DEBUG

    }

    /// \brief Default destructor.
    ///
    /// Default destructor.
    virtual ~Cell()
    {

#ifdef DEBUG
        --counter;
#endif // DEBUG

    }

    // Print function.
    friend ostream&
    operator<<(ostream& os,
               const Cell& c);

    /// \brief Get zone.
    ///
    /// Get zone.
    ///
    /// \return
    /// Zone.
    inline Zone*
    get_zone()
    {
        return zone;
    }

    /// \brief Link to zone.
    ///
    /// Link to zone.
    ///
    /// \param[in] z Zone.
    inline void
    link_zone(Zone* z)
    {
        zone = z;
    }

    // Get neighbour through the edge.
    Cell*
    get_neighbour(Edge* e);

    // Fill list of neighbours by nodes.
    void
    get_neighbours_by_nodes(vector<Cell*>& ngh);

    // Init fictitious points.
    void
    init_fictitious_points();

    // Init neighbourhood.
    void
    init_neighbourhood();

    /// \brief Get neighbourhood.
    ///
    /// Get neighbourhood.
    ///
    /// \return
    /// Neighbourhood.
    inline const vector<Cell*>&
    get_neighbourhood() const
    {
        return neighbourhood;
    }

    //
    // Data access.
    //

    /// \brief Get domain.
    ///
    /// Get domain.
    ///
    /// \return
    /// Domain.
    inline size_t
    get_domain() const
    {
        return domain;
    }

    /// \brief Get area (m^2).
    ///
    /// Get area (m^2).
    ///
    /// \return
    /// Area (m^2).
    inline double
    get_area() const
    {
        return area;
    }

    /// \brief Get center vector.
    ///
    /// Get center vector.
    ///
    /// \return
    /// Center vector.
    inline const geom::Vector&
    get_center() const
    {
        return center;
    }

    /// \brief Get normal.
    ///
    /// Get normal.
    ///
    /// \return
    inline const geom::Vector&
    get_normal() const
    {
        return normal;
    }

    /// \brief Get data from cell.
    ///
    /// Get data from cell.
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
        CellDataElement cde { static_cast<CellDataElement>(index) };

        switch (cde)
        {
            case CellDataElement::CellMark:
                return get_mark();

            case CellDataElement::CellId:
                return get_id();

            case CellDataElement::Domain:
                return static_cast<double>(domain);

            case CellDataElement::Area:
                return area;

            case CellDataElement::NormalX:
                return normal.x;

            case CellDataElement::NormalY:
                return normal.y;

            case CellDataElement::NormalZ:
                return normal.z;

            case CellDataElement::FictitiousNormalX:
                return fictitious_normal.x;

            case CellDataElement::FictitiousNormalY:
                return fictitious_normal.y;

            case CellDataElement::FictitiousNormalZ:
                return fictitious_normal.z;

            default:
                return get_data<TData>()->get_data_element(index);
        }
    }

    /// \brief Set data to cell.
    ///
    /// Set data to cell.
    ///
    /// \tparam    TData           Type of data.
    /// \param[in] index           Index of data element.
    /// \param[in] v               Value.
    /// \param[in] is_debug_ignore Debug ignore if we try to set fild not intended for it
    template<typename TData>
    void
    set_data_element(int index,
                     double v,
                     bool is_debug_ignore = false)
    {
        CellDataElement cde { static_cast<CellDataElement>(index) };

        (void)is_debug_ignore;

        switch (cde)
        {
            case CellDataElement::CellMark:
                set_mark(static_cast<int>(v));
                break;

            case CellDataElement::CellId:
            case CellDataElement::Domain:
            case CellDataElement::Area:
            case CellDataElement::NormalX:
            case CellDataElement::NormalY:
            case CellDataElement::NormalZ:
            case CellDataElement::FictitiousNormalX:
            case CellDataElement::FictitiousNormalY:
            case CellDataElement::FictitiousNormalZ:
                DEBUG_CHECK_ERROR(is_debug_ignore, "unable to set cell data element "
                                                   + CellDataElementMapper.get_name(cde));
                break;

            default:
                get_data<TData>()->set_data_element(index, v);
                break;
        }
    }

    //
    // Geometry.
    //

    /// Calculate area.
    void
    calc_area();

    /// Calculate center point.
    void
    calc_center();

    // Calculate outer normal.
    void
    calc_outer_normal();

    // Calculate fictitious outer normal.
    void
    calc_fictitious_outer_normal();
};

/// @}

}

}

#endif // !CAESAR_MESH_CELL_H
