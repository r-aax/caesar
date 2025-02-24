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
#include "mesh_geometrical.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Unstructured surface mesh.
class Mesh
    : public Geometrical
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

    //
    // Control memory leaks.
    //

#ifdef DEBUG
    static int counter;
#endif // DEBUG

    //
    // Constructors/destructors.
    //

    // Constructor.
    Mesh();

    // Destructor.
    virtual
    ~Mesh();

    //
    // Access to zones.
    //

    /// \brief Get zone (const version).
    ///
    /// Get zone (const version).
    ///
    /// \param[in] i Index of zone.
    ///
    /// \return
    /// Pointer to zone (const version).
    inline const Zone*
    zone(size_t i) const
    {
        return zones[i];
    }

    /// \brief Get zone.
    ///
    /// Get zone.
    ///
    /// \param[in] i Index of zone.
    ///
    /// \return
    /// Pointer to zone.
    inline Zone*
    zone(size_t i)
    {
        return zones[i];
    }

    //
    // Free data.
    //

private:

    /// \brief Free data if not null.
    ///
    /// \tparam TNodeData Node data type.
    /// \tparam TEdgeData Edge data type.
    /// \tparam TCellData Cell data type.
    template<typename TNodeData,
             typename TEdgeData,
             typename TCellData>
    void
    free_data_if_not_null()
    {
        size_t nc { all.nodes_count() }, ec { all.edges_count() }, cc { all.cells_count() };

        // Delete nodes.
        for (size_t i = 0; i < nc; ++i)
        {
            Node* n { all.node(i) };

            n->free_data_if_not_null<TNodeData>();
        }

        // Delete edges.
        for (size_t i = 0; i < ec; ++i)
        {
            Edge* e { all.edge(i) };

            e->free_data_if_not_null<TEdgeData>();
        }

        // Delete cells.
        for (size_t i = 0; i < cc; ++i)
        {
            Cell* c { all.cell(i) };

            c->free_data_if_not_null<TCellData>();
        }
    }

public:

    /// \brief Clear mesh.
    ///
    /// \tparam TNodeData Node data type.
    /// \tparam TEdgeData Edge data type.
    /// \tparam TCellData Cell data type.
    template<typename TNodeData,
             typename TEdgeData,
             typename TCellData>
    void
    clear()
    {
        size_t nc { all.nodes_count() }, ec { all.edges_count() }, cc { all.cells_count() };
        size_t zc { zones_count() };

        free_data_if_not_null<TNodeData, TEdgeData, TCellData>();

        // Delete nodes.
        for (size_t i = 0; i < nc; ++i)
        {
            Node* n { all.node(i) };

            delete n;
        }

        // Delete edges.
        for (size_t i = 0; i < ec; ++i)
        {
            Edge* e { all.edge(i) };

            delete e;
        }

        // Delete cells.
        for (size_t i = 0; i < cc; ++i)
        {
            Cell* c { all.cell(i) };

            delete c;
        }

        // Delete zones.
        for (size_t i = 0; i < zc; ++i)
        {
            Zone* z { zone(i) };

            delete z;
        }

        // Clear all the rest.
        title = "";
        variables_names.clear();
        varlocation_cellcentered.first = 0;
        varlocation_cellcentered.second = 0;
        zones.clear();
        all.clear();
        own.clear();

        // issue #39
        // Do not clear own edges by colors vector and histogram.
        // Size of own_edges_by_colors and own_edges_colors_histogram must be constant.
        for (size_t i = 0; i < max_edges_colors_count; ++i)
        {
            own_edges_by_colors[i].clear();
            own_edges_colors_histogram[i] = 0;
        }

        domains_cells.clear();
    }

    /// \brief Clear mesh.
    ///
    /// Clear mesh with default data.
    void
    clear()
    {
        clear<NodeDataStub, EdgeDataStub, CellDataStub>();
    }

    //
    // Print functions.
    //

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
        size_t cc { node->cells_count() };

        double v { 0.0 };

        for (size_t i = 0; i < cc; ++i)
        {
            Cell* c { node->cell(i) };

            v += c->get_element<TData>(index);
        }

        return v / static_cast<double>(cc);
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
    // Set variables names for mesh storing.
    //

    // Set variables names.
    void
    set_variables_names(const vector<string>& nodes_variables_names,
                        const vector<string>& cells_variables_names);

    //
    // Objects links.
    //

    // Find zone.
    Zone*
    find_zone(const string& name) const;

    // Find node.
    Node*
    find_node(const geom::Vector& point);

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
        size_t aec { a->edges_count() };

        // Check all edges.
        for (size_t i = 0; i < aec; ++i)
        {
            Edge* e { a->edge(i) };

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

    // Init cells neighbourhoods.
    void
    init_cells_neighbourhoods();

    //
    // Mark functions.
    //

    // Mark cells.
    void
    mark_cells(bool (*cond)(Cell*));

    // Mark border nodes and cells.
    void
    mark_mesh_border_nodes_and_cells();

    //
    // Geometry.
    //

    // Calculate geometry.
    void
    calc_geometry();

    // Save geometry.
    void
    save_geometry();

    // Restore geometry.
    void
    restore_geometry();

    //
    // Layers.
    //

    /// \brief Save layer.
    ///
    /// \tparam TCellData Cell data type.
    ///
    /// Copy new layer to old layer.
    template<typename TCellData>
    void
    save_layer()
    {
        size_t cc { all.cells_count() };

        #pragma omp parallel for
        for (size_t i = 0; i < cc; ++i)
        {
            Cell* c { all.cell(i) };

            c->get_data<TCellData>()->save_layer();
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
        size_t cc { all.cells_count() };

        #pragma omp parallel for
        for (size_t i = 0; i < cc; ++i)
        {
            Cell* c { all.cell(i) };

            c->get_data<TCellData>()->restore_layer();
        }
    }

    //
    // Data access.
    //

    /// \brief Get nodes elements from mesh nodes.
    ///
    /// Get nodes elements from mesh nodes.
    ///
    /// \tparam               Type of node data.
    /// \param[in]  index     Index of element.
    /// \param[out] data      Array for data.
    /// \param[in]  max_count Maximum count of read element.
    template<typename TNodeData>
    void
    get_nodes_elements(int index,
                       double* data,
                       int max_count = numeric_limits<int>::max())
    {
        size_t n { all.nodes_count() };
        int count { 0 };

        for (size_t i = 0; i < n; ++i)
        {
            data[i] = all.node(i)->get_element<TNodeData>(index);

            ++count;

            if (count == max_count)
            {
                break;
            }
        }
    }

    /// \brief Set nodes elements to mesh nodes.
    ///
    /// Set nodes elements to mesh nodes.
    ///
    /// \tparam              Type of node data.
    /// \param[in] index     Index of element.
    /// \param[in] data      Source data.
    /// \param[in] max_count Maximum count of set element.
    template<typename TNodeData>
    void
    set_nodes_elements(int index,
                       double* data,
                       int max_count = numeric_limits<int>::max())
    {
        size_t n { all.nodes_count() };
        int count { 0 };

        for (size_t i = 0; i < n; ++i)
        {
            all.node(i)->set_element<TNodeData>(index, data[i]);

            ++count;

            if (count == max_count)
            {
                break;
            }
        }
    }

    /// \brief Set data element for all mesh cells.
    ///
    /// Set data element for all mesh cells.
    ///
    /// \tparam    TCellData Type of cell data.
    /// \param[in] index     Index of element.
    /// \param[in] v         Value.
    template<typename TCellData>
    void
    set_all_cells_element(int index,
                          double v)
    {
        size_t cc { all.cells_count() };

        #pragma omp parallel for
        for (size_t i = 0; i < cc; ++i)
        {
            Cell* c { all.cell(i) };

            c->set_element<TCellData>(index, v);
        }
    }

    /// \brief Set data element for all mesh cells if data is not initialized.
    ///
    /// Set data element for all mesh cells if data is not initialized.
    ///
    /// \tparam    TCellData Type of cell data.
    /// \param[in] index     Index of element.
    /// \param[in] v         Value.
    template<typename TCellData>
    void
    set_all_cells_uninitialized_element(int index,
                                        double v)
    {
        size_t cc { all.cells_count() };

        #pragma omp parallel for
        for (size_t i = 0; i < cc; ++i)
        {
            Cell* c { all.cell(i) };

            if (std::isnan(c->get_element<TCellData>(index)))
            {
                c->set_element<TCellData>(index, v);
            }
        }
    }

    /// \brief Get cells elements from mesh cells.
    ///
    /// Get cells elements from mesh cells.
    ///
    /// \tparam               Type of cell data.
    /// \param[in]  index     Index of element.
    /// \param[out] data      Array for data.
    /// \param[in]  max_count Maximum count of read element.
    template<typename TCellData>
    void
    get_cells_elements(int index,
                       double* data,
                       int max_count = numeric_limits<int>::max())
    {
        size_t n { all.cells_count() };
        int count { 0 };

        for (size_t i = 0; i < n; ++i)
        {
            data[i] = all.cell(i)->get_element<TCellData>(index);

            ++count;

            if (count == max_count)
            {
                break;
            }
        }
    }

    /// \brief Set cells elements to mesh cells.
    ///
    /// Set cells elements to mesh cells.
    ///
    /// \tparam              Type of cell data.
    /// \param[in] index     Index of element.
    /// \param[in] data      Source data.
    /// \param[in] max_count Maximum count of set element.
    template<typename TCellData>
    void
    set_cells_elements(int index,
                       double* data,
                       int max_count = numeric_limits<int>::max())
    {
        size_t n { all.cells_count() };
        int count { 0 };

        for (size_t i = 0; i < n; ++i)
        {
            all.cell(i)->set_element<TCellData>(index, data[i]);

            ++count;

            if (count == max_count)
            {
                break;
            }
        }
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
