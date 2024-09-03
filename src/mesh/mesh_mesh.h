/// \file
/// \brief Unstructured surface mesh declaration.
///
/// Declaration of unstructured surface mesh.

#ifndef CAESAR_MESH_MESH_H
#define CAESAR_MESH_MESH_H

#include "utils/utils.h"
#include "mesh_zone.h"
#include "mesh_boundaries.h"
#include "mesh_nodes_edges_cells_holder.h"
#include "mesh_node_data_stub.h"
#include "mesh_edge_data_stub.h"
#include "mesh_cell_data_stub.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Unstructured surface mesh.
class Mesh
{
    friend class Remesher;
    friend class Decomposer;

private:

    /// \brief Maximum count of edges colors.
    ///
    /// We can guarantee we can paint surface mesh edges in 5 colors.
    const size_t max_edges_colors_count { 5 };

public:

    /// \brief Title.
    string title { "" };

    /// \brief Variables names.
    vector<string> variables_names;

    /// \brief Varlocation cellcentered variables.
    pair<size_t, size_t> varlocation_cellcentered { 0, 0 };

private:

    /// \brief Zones list.
    vector<Zone*> zones;

public:

    /// \brief Holder for all elements.
    NodesEdgesCellsHolder all;

    /// \brief Holder for own elements.
    NodesEdgesCellsHolder own;

private:

    /// \brief Own edges by colors.
    vector<vector<Edge*>> own_edges_by_colors;

    /// \brief Own edges colors histogram.
    vector<int> own_edges_colors_histogram;

    /// \brief Cells for gather.
    vector<vector<Cell*>> domains_cells;

    /// \brief Information about borders.
    Boundaries boundaries;

    /// \brief Data gatherrer.
    parl::OneToAllExchanger gatherer;

public:

#ifdef DEBUG
    static int counter;
#endif // DEBUG

    // Constructor.
    Mesh();

    // Destructor.
    virtual
    ~Mesh();

    /// \brief Free data if not null.
    ///
    /// \tparam TNodeData Node data type.
    /// \tparam TEdgeData Edge data type.
    /// \tparam TCellData Cell data type.
    template<typename TNodeData,
             typename TEdgeData,
             typename TCellData>
    void
    free_data_if_null()
    {
        // Delete nodes.
        for (auto n : all.nodes())
        {
            n->free_data_if_not_null<TNodeData>();
        }

        // Delete edges.
        for (auto e : all.edges())
        {
            e->free_data_if_not_null<TEdgeData>();
        }

        // Delete cells.
        for (auto c : all.cells())
        {
            c->free_data_if_not_null<TCellData>();
        }
    }

    /// \brief Default free data.
    ///
    /// Default free data.
    void
    free_data_if_null()
    {
        free_data_if_null<NodeDataStub, EdgeDataStub, CellDataStub>();
    }

    // Print information.
    void
    print_info(ostream& s = cout,
               bool is_print_elements = false) const;

    // Print mesh elements.
    void
    print_elements(const vector<int>& nodes_ids_range,
                   const vector<int>& edges_ids_range,
                   const vector<int>& cells_ids_range,
                   ostream& s = cout) const;

    //
    // Access to objects lists.
    //

    /// \brief Get zones list.
    ///
    /// Get zones list.
    ///
    /// \return
    /// Zones list.
    inline vector<Zone*>&
    get_zones()
    {
        return zones;
    }

    //
    // Get numbers of objects.
    //

    /// \brief Get zones count.
    ///
    /// Get zones count.
    ///
    /// \return
    /// Zones count.
    inline size_t
    zones_count() const
    {
        return zones.size();
    }

    /// \brief Get mean data of cells around the node.
    ///
    /// Get mean data of cells around the node.
    ///
    /// \tparam    TData Type of data.
    /// \param[in] node  Node.
    /// \param[in] index Cell data element index.
    ///
    /// \return
    /// Value.
    template<typename TData>
    double
    get_node_cells_mean_data(Node* node,
                             int index) const
    {
        size_t cnt { node->cells_count() };

        double v { 0.0 };

        for (auto c : node->cells())
        {
            v += c->get_element<TData>(index);
        }

        return v / static_cast<double>(cnt);
    }

    //
    // Init identifiers.
    //

    // Init global identifiers.
    void
    init_global_identifiers();

    // Init local identifiers.
    void
    init_local_identifiers();

    /// \brief Add color to own edges colors histogram.
    ///
    /// Add color to own edges colors histogram.
    ///
    /// \param[in] color Color.
    inline void
    add_color_to_own_edges_colors_histogram(int color)
    {
        ++own_edges_colors_histogram[static_cast<size_t>(color)];
    }

    // Register edge's color.
    void
    register_edge_color(Edge* e,
                        int c);

    // Check own edges colors distribution correctness.
    bool
    is_own_edges_colors_distribution_correct() const;

    //
    // Objects links.
    //

    // Find zone.
    Zone*
    find_zone(const string& name) const;

    // Find node.
    Node*
    find_node(const geom::Vector& point) const;

    /// \brief Find or add edge.
    ///
    /// Find edge between two nodes.
    /// If there is no such edge, then add it.
    ///
    /// \tparam    TEdgeData Type of edge data.
    /// \param[in] a         First node.
    /// \param[in] b         Second node.
    ///
    /// \return
    /// Found or added edge.
    template<typename TEdgeData>
    Edge*
    find_or_add_edge(Node* a,
                     Node* b)
    {
        // Check all edges.
        for (auto e : a->edges())
        {
            if ((e->node(0) == a) && (e->node(1) == b))
            {
                return e;
            }

            if ((e->node(0) == b) && (e->node(1) == a))
            {
                return e;
            }
        }

        // No edge - add new one.
        Edge* e = new Edge();

        // Allocate data for edge.
        e->allocate_data<TEdgeData>();

        e->add_node(a);
        a->add_edge(e);
        e->add_node(b);
        b->add_edge(e);
        all.add_edge(e);

        return e;
    }

    // Distribute edges between zones.
    void
    distribute_edges_between_zones();

    // Mark border nodes and cells.
    void
    mark_mesh_border_nodes_and_cells();

    // Init cells neighbourhoods.
    void
    init_cells_neighbourhoods();

    //
    // Geometry.
    //

    // Update cells geometry.
    void
    update_cells_geometry();

    // Update geometry.
    void
    update_geometry();

    // Update fictitious geometry.
    void
    update_fictitious_geometry();

    // Restore nodes points.
    void
    restore_nodes_point();

    /// \brief Age layer.
    ///
    /// \tparam TCellData Cell data type.
    ///
    /// Copy new layer to old layer.
    template<typename TCellData>
    void
    age_layer()
    {
        #pragma omp parallel for
        for (auto c : all.cells())
        {
            c->get_data<TCellData>()->age_layer();
        }
    }

    /// \brief Restore layer.
    ///
    /// \tparam TCellData Cell data type.
    ///
    /// Copy old layer to new layer.
    template<typename TCellData>
    void
    restore_layer()
    {
        #pragma omp parallel for
        for (auto c : all.cells())
        {
            c->get_data<TCellData>()->restore_layer();
        }
    }

    /// \brief Save before remesh.
    ///
    /// Save layer and point before remesh.
    ///
    /// \tparam TCellData Cell data type.
    template<typename TCellData>
    void
    save_before_remesh()
    {
        age_layer<TCellData>();
    }

    /// \brief Restore after remesh.
    ///
    /// Restore layer and point after remesh.
    ///
    /// \tparam TCellData Cell data type.
    template<typename TCellData>
    void
    restore_after_remesh()
    {
        restore_nodes_point();
        restore_layer<TCellData>();
        update_geometry();
    }

    //
    // Data transfers.
    //

    /// \brief Exchanges of data.
    ///
    /// Data exchnages through boundaries.
    ///
    /// \tparam TCellData Cell data type.
    ///
    /// \param[in] index Index of element.
    template<typename TCellData>
    void
    exchange(int index)
    {
        boundaries.write_to_buffers<TCellData>(index);
        boundaries.exchange();
        boundaries.read_from_buffers<TCellData>(index);
    }

    /// \brief Gather data in process 0.
    ///
    /// Gather some element of data on process 0.
    ///
    /// \tparam    TCellData Cell data type.
    /// \param[in] index     Index of element.
    template<typename TCellData>
    void
    gather(int index)
    {
        size_t s = parl::mpi_size();
        size_t r = parl::mpi_rank();

        // Write data to out buffer if it is not process 0.
        if (r != 0)
        {
            vector<double>& buffer = gatherer.get_out_data(0);

            for (size_t i = 0; i < domains_cells[r].size(); ++i)
            {
                buffer[i] = domains_cells[r][i]->get_element<TCellData>(index);
            }
        }

        // Gather data.
        gatherer.gather();

        // Read data from in buffers for process 0.
        if (r == 0)
        {
            for (size_t ri = 1; ri < s; ++ri)
            {
                vector<double>& buffer = gatherer.get_in_data(ri - 1);

                for (size_t i = 0; i < domains_cells[ri].size(); ++i)
                {
                    domains_cells[ri][i]->set_element<TCellData>(index, buffer[i]);
                }
            }
        }
    }
};

/// @}

}

}

#endif // !CAESAR_MESH_MESH_H
