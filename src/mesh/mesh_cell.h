/// \file
/// \brief Mesh cell declaration.
///
/// Mesh cell declaration.

#ifndef CAESAR_MESH_CELL_H
#define CAESAR_MESH_CELL_H

#include "mesh_cell_element.h"
#include "mesh_edge.h"
#include "mesh_nodes_holder.h"
#include "mesh_edges_holder.h"
#include "mesh_geometrical.h"
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
      public EdgesHolder,
      public Geometrical
{
    friend class Node;
    friend class Edge;
    friend class Zone;
    friend class Mesh;
    friend class Filer;
    friend class Remesher;
    friend class Decomposer;

public:

    /// \brief Domain number.
    ///
    /// By default there is only one domain with number zero.
    size_t domain { 0 };

    /// \brief Zone.
    Zone* zone { nullptr };

    /// \brief Links to neighbourhood.
    vector<Cell*> neighbourhood;

private:

    //
    // Geometry data.
    //

    /// \brief Original area.
    ///
    /// Original area.
    double original_area_ { 0.0 };

    /// \brief Current area.
    ///
    /// Current area.
    double area_ { 0.0 };

    /// \brief Original center.
    ///
    /// Original center.
    geom::Vector original_center_;

    /// \brief Center.
    ///
    /// Center.
    geom::Vector center_;

    /// \brief Original normal.
    ///
    /// Original normal.
    geom::Vector original_normal_;

    /// \brief Normal.
    ///
    /// Normal.
    geom::Vector normal_;

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

    /// \brief Saved area.
    double saved_area { 0.0 };

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

    //
    // Print.
    //

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

    //
    // Work with geometry.
    //

    /// \brief Get area (m^2).
    ///
    /// Get area (m^2).
    ///
    /// \return
    /// Area (m^2).
    inline double
    area() const
    {
        return area_;
    }

    /// \brief Get center vector.
    ///
    /// Get center vector.
    ///
    /// \return
    /// Center vector.
    inline const geom::Vector&
    center() const
    {
        return center_;
    }

    /// \brief Get normal.
    ///
    /// Get normal.
    ///
    /// \return
    inline const geom::Vector&
    normal() const
    {
        return normal_;
    }

private:

    /// Calculate area.
    void
    calc_area();

    /// Calculate center point.
    void
    calc_center();

    // Calculate outer normal.
    void
    calc_normal();

public:

    /// \brief Calculate geometry.
    ///
    /// Calculate geometry.
    inline void
    calc_geometry()
    {
        calc_area();
        calc_center();
        calc_normal();
    }

    /// \brief Save geometry.
    ///
    /// Save geometry.
    inline void
    save_geometry()
    {
        original_area_ = area_;
        original_center_.set(center_);
        original_normal_.set(normal_);
    }

    /// \brief Restore geometry.
    ///
    /// Restore geometry.
    inline void
    restore_geometry()
    {
        area_ = original_area_;
        center_.set(original_center_);
        normal_.set(original_normal_);
    }

    //
    // Data access.
    //

    /// \brief Get element from cell.
    ///
    /// Get element from cell.
    ///
    /// \tparam    TData Type of data.
    /// \param[in] index Index of data element.
    ///
    /// \return
    /// Value.
    template<typename TData>
    double
    get_element(int index) const
    {
        CellElement ce { static_cast<CellElement>(index) };

        switch (ce)
        {
            case CellElement::CellMark:
                return get_mark();

            case CellElement::CellId:
                return get_id();

            case CellElement::Domain:
                return static_cast<double>(domain);

            case CellElement::Area:
                return area_;

            case CellElement::NormalX:
                return normal_.x;

            case CellElement::NormalY:
                return normal_.y;

            case CellElement::NormalZ:
                return normal_.z;

            default:
                return get_data<TData>()->get_element(index);
        }
    }

    /// \brief Set data to cell.
    ///
    /// Set data to cell.
    ///
    /// \tparam    TData Type of data.
    /// \param[in] index Index of element.
    /// \param[in] v     Value.
    template<typename TData>
    void
    set_element(int index,
                double v)
    {
        CellElement ce { static_cast<CellElement>(index) };

        switch (ce)
        {
            case CellElement::CellMark:
                set_mark(static_cast<int>(v));
                break;

            case CellElement::CellId:
            case CellElement::Domain:
            case CellElement::Area:
            case CellElement::NormalX:
            case CellElement::NormalY:
            case CellElement::NormalZ:
                DEBUG_ERROR("unable to set cell data element " + CellElementMapper.get_name(ce));
                break;

            default:
                get_data<TData>()->set_element(index, v);
                break;
        }
    }

    /// \brief Get derivative of data by given direction.
    ///
    /// Get derivative of data by given direction.
    ///
    /// \tparam    TData Cell data.
    /// \param[in] index Data index.
    /// \param[in] d     Direction
    ///
    /// \return
    /// Derivative by direction.
    template<typename TData>
    double
    derivative_by_direction(int index,
                            const geom::Vector& d)
    {
        // We consider all cell neighbours by nodes but filter them by condition:
        // the angle between direction to the neighbour and tau vector is far from straight angle.
        static const double cos_threshold { 1.0 / sqrt(2.0) };

        // Avoid neighbours to close to our cell.
        static const double min_dr { 1.0e-6 };

        // Avoid too small tau vector.
        static const double min_d_mod { 1.0e-6 };

        vector<double> ps;

        if (d.mod() > min_d_mod)
        {
            vector<mesh::Cell*> nghs;

            // Calculate dp_dtau through all neighbours by nodes.
            get_neighbours_by_nodes(nghs);

            for (auto ngh : nghs)
            {
                geom::Vector direction;

                geom::Vector::sub(ngh->center(), center(), direction);

                // Filter by angle.
                if (abs(geom::Vector::angle_cos(d, direction)) > cos_threshold)
                {
                    double dv { ngh->get_element<TData>(index) - get_element<TData>(index) };
                    double dr { direction.projection_value(d) };

                    // Filter close cells.
                    if (abs(dr) > min_dr)
                    {
                        ps.push_back(dv / dr);
                    }
                }
            }
        }

        // If we have no good neighbours for calculate derivative, make it const.
        return (ps.empty()) ? 0.0 : mth::mean(ps);
    }
};

/// @}

}

}

#endif // !CAESAR_MESH_CELL_H
