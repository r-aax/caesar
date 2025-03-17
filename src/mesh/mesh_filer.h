/// \file
/// \brief Class for work with files.
///
/// Load/store mesh and mesh statistics.

#ifndef MESH_FILER_H
#define MESH_FILER_H

#include <set>
#include <fstream>

#include "mesh_mesh.h"
#include "mesh_node_data_stub.h"
#include "mesh_edge_data_stub.h"
#include "mesh_cell_data_stub.h"
#include "utils/utils.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Manager for work with files.
///
/// Load and store meshes.
class Filer
{

public:

    /// \brief Get zone links from string.
    ///
    /// Get links from string.
    ///
    /// \tparam        TEdgeData  Data of edge.
    /// \param[in,out] mesh       Mesh.
    /// \param[in,out] zone       Zone.
    /// \param[in]     s          String.
    /// \param[in]     cell_index Cell index.
    template<typename TEdgeData>
    static void
    get_zone_links_from_string(Mesh& mesh,
                               Zone* zone,
                               const string& s,
                               size_t cell_index)
    {
        size_t p { 0 };
        size_t len { 0 };
        vector<size_t> links;

        while (utils::find_word(s, p, p, len))
        {
            links.push_back(static_cast<size_t>(stoi(s.substr(p, len))));
            p += (len + 1);
        }

        // Links has 3 integers.
        DEBUG_CHECK_ERROR(links.size() == 3, "wrong element-node link line");

        // Objects.
        Cell* c = zone->cell(cell_index);
        Node* n0 = zone->node(links[0] - 1);
        Node* n1 = zone->node(links[1] - 1);
        Node* n2 = zone->node(links[2] - 1);
        Edge* e01 = mesh.find_or_add_edge<TEdgeData>(n0, n1);
        Edge* e12 = mesh.find_or_add_edge<TEdgeData>(n1, n2);
        Edge* e20 = mesh.find_or_add_edge<TEdgeData>(n2, n0);

        // Set links.
        link_node_cell(n0, c);
        link_node_cell(n1, c);
        link_node_cell(n2, c);
        link_edge_cell(e01, c);
        link_edge_cell(e12, c);
        link_edge_cell(e20, c);
    }

    /// \brief Build zone nodes and cells.
    ///
    /// Build zone nodes and cells.
    ///
    /// \tparam         TNodeData                Node data.
    /// \tparam         TNodeDataElement         Node data mapper.
    /// \tparam         TCellData                Cell data.
    /// \tparam         TCellDataElement         Cell data mapper.
    /// \param[in,out]  mesh                     Mesh.
    /// \param[in,out]  zone                     Zone.
    /// \param[in]      data                     Data.
    /// \param[in, out] points_bag               Bag of points.
    /// \param[in]      node_data_element_mapper Mapper for node data.
    /// \param[in]      cell_data_element_mapper Mapper for cell data.
    template<typename TNodeData,
             typename TNodeDataElement,
             typename TCellData,
             typename TCellDataElement>
    static void
    build_zone_nodes_and_cells(Mesh& mesh,
                               Zone* zone,
                               vector<vector<double>>& data,
                               set<uint64_t>& points_bag,
                               utils::Mapper<TNodeDataElement>& node_data_element_mapper,
                               utils::Mapper<TCellDataElement>& cell_data_element_mapper)
    {
        // Checkers.
        DEBUG_CHECK_ERROR(mesh.variables_names[0] == "X", "first data element must be X");
        DEBUG_CHECK_ERROR(mesh.variables_names[1] == "Y", "second data element must be Y");
        DEBUG_CHECK_ERROR(mesh.variables_names[2] == "Z", "third data element must be Z");
        DEBUG_CHECK_ERROR(data.size() == mesh.varlocation_cellcentered.second, "wrong count of data elements");

#ifdef DEBUG

        // Check data elements sizes.

        for (size_t v = 0; v < mesh.varlocation_cellcentered.first - 1; ++v)
        {
            DEBUG_CHECK_ERROR(data[v].size() == zone->expected_nodes_count,
                              "wrong size of nodes data array");
        }

        for (size_t v = mesh.varlocation_cellcentered.first - 1;
             v < mesh.varlocation_cellcentered.second;
             ++v)
        {
            DEBUG_CHECK_ERROR(data[v].size() == zone->expected_elements_count,
                              "wrong size of cells data array");
        }

#endif // DEBUG

        // Build nodes.
        // Add all nodes to mesh list, and to local zone nodes list.
        for (size_t i = 0; i < zone->expected_nodes_count; ++i)
        {
            // Make new node.
            Node* new_node = new Node(data[0][i], data[1][i], data[2][i]);

            // Allocate data for node.
            new_node->allocate_data<TNodeData>();

            // Calculate hash.
            uint64_t h = new_node->point().hash();

            if (points_bag.find(h) == points_bag.end())
            {
                // No such hash in set - so no such node.
                // We need to add new node.
                points_bag.insert(h);
                mesh.all.add_node(new_node);
                zone->add_node(new_node);
            }
            else
            {
                // Try to find node.
                Node* found_node = mesh.find_node(new_node->point());

                if (!found_node)
                {
                    // No such node, add it.
                    mesh.all.add_node(new_node);
                    zone->add_node(new_node);
                }
                else
                {
                    // Node is found, so delete created node and use the old one.

                    new_node->free_data<TNodeData>();
                    delete new_node;
                    zone->add_node(found_node);
                }
            }
        }

        // Init nodes.
        for (size_t v = 3; v < mesh.varlocation_cellcentered.first - 1; ++v)
        {
            string name { mesh.variables_names[v] };
            int index = NodeElementMapper.has(name)
                        ? static_cast<int>(NodeElementMapper.get_enum(name))
                        : static_cast<int>(node_data_element_mapper.get_enum(name));

            for (size_t i = 0; i < zone->nodes_count(); ++i)
            {
                zone->node(i)->set_element<TNodeData>(index, data[v][i]);
            }
        }

        // Build cells.
        for (size_t i = 0; i < zone->expected_elements_count; ++i)
        {
            Cell* cell = new Cell();

            // Allocate data for cell.
            cell->allocate_data<TCellData>();

            cell->link_zone(zone);
            mesh.all.add_cell(cell);
            zone->add_cell(cell);
        }

        // Init cells.
        for (size_t v = mesh.varlocation_cellcentered.first - 1;
             v < mesh.varlocation_cellcentered.second;
            ++v)
        {
            string name { mesh.variables_names[v] };
            int index = CellElementMapper.has(name)
                        ? static_cast<int>(CellElementMapper.get_enum(name))
                        : static_cast<int>(cell_data_element_mapper.get_enum(name));

            for (size_t i = 0; i < zone->cells_count(); ++i)
            {
                zone->cell(i)->set_element<TCellData>(index, data[v][i]);
            }
        }
    }

    /// \brief Load mesh.
    ///
    /// \tparam        TNodeData                Node data.
    /// \tparam        TNodeDataElement         Node data mapper.
    /// \tparam        TEdgeData                Data of edge.
    /// \tparam        TCellData                Cell data.
    /// \tparam        TCellDataElement         Cell data mapper.
    /// \param[in,out] mesh                     Mesh to be loaded.
    /// \param[in]     fn                       Name of file.
    /// \param[in]     node_data_element_mapper Mapper for node data.
    /// \param[in]     cell_data_element_mapper Mapper for cell data.
    ///
    /// \return
    /// true - if loading is complete,
    /// false - otherwise.
    template<typename TNodeData,
             typename TNodeDataElement,
             typename TEdgeData,
             typename TCellData,
             typename TCellDataElement>
    static bool
    load_mesh(Mesh& mesh,
              const string& fn,
              utils::Mapper<TNodeDataElement>& node_data_element_mapper,
              utils::Mapper<TCellDataElement>& cell_data_element_mapper)
    {
        // Clear mesh before load it again.
        mesh.clear<TNodeData, TEdgeData, TCellData>();

        ifstream f(fn);
        string line { "" };
        Zone* current_zone{ nullptr };

        // Data got from zone.
        vector<vector<double>> data;

        // Bag of points.
        set<uint64_t> points_bag;

        if (!f.is_open())
        {
            DEBUG_ERROR("no file " + fn + " found");

            return false;
        }

        // We do not load meshes more than one time.
        if (mesh.zones_count() > 0)
        {
            DEBUG_ERROR("mesh is already loaded");
        }

        while (getline(f, line))
        {
            if (line.empty())
            {
                // Ignore empty line.
                ;
            }
            else if (line[0] == '#')
            {
                // Ignore comment line.
                ;
            }
            else if (utils::str_starts_with(line, "TITLE="))
            {
                // Get title.
                get_mesh_title_from_string(mesh, line);
            }
            else if (utils::str_starts_with(line, "VARIABLES="))
            {
                // Get variables names.
                get_mesh_variables_names_from_string(mesh, line);
            }
            else if (utils::str_starts_with(line, "ZONE T="))
            {
                // Get zone name.

                // It is the time for us to create new zone.
                mesh.get_zones().push_back(new Zone());
                current_zone = mesh.get_zones().back();

                // Get its name.
                get_zone_name_from_string(current_zone, line);
            }
            else if (utils::str_starts_with(line, "NODES="))
            {
                // Get nodes count.
                get_zone_nodes_count_from_string(current_zone, line);
            }
            else if (utils::str_starts_with(line, "ELEMENTS="))
            {
                // Get elements count.
                get_zone_elements_count_from_string(current_zone, line);
            }
            else if (utils::str_starts_with(line, "DATAPACKING="))
            {
                // Get datapacking type.
                // Now only BLOCK is supported.
                DEBUG_CHECK_ERROR(utils::str_starts_with(line, "DATAPACKING=BLOCK"), "only BLOCK datapacking is supported");
            }
            else if (utils::str_starts_with(line, "ZONETYPE="))
            {
                // Get zone type.
                // Now only FETRIANGLE is supported.
                DEBUG_CHECK_ERROR(utils::str_starts_with(line, "ZONETYPE=FETRIANGLE"), "only FETRIANLE zone type is supported");
            }
            else if (utils::str_starts_with(line, "VARLOCATION="))
            {
                // Get varlocation.
                get_zone_varlocation_cellcentered_from_string(mesh, line);
            }
            else
            {
                // First line of data.
                get_zone_data_from_string(data, line);

                // Rest lines of data.
                for (size_t i = 1; i < mesh.variables_names.size(); ++i)
                {
                    getline(f, line);
                    get_zone_data_from_string(data, line);
                }

                // Allocate memory for nodes and cells.
                build_zone_nodes_and_cells<TNodeData,
                                           TNodeDataElement,
                                           TCellData,
                                           TCellDataElement>(mesh,
                                                             current_zone,
                                                             data,
                                                             points_bag,
                                                             node_data_element_mapper,
                                                             cell_data_element_mapper);

                // Free extra memory.
                data.clear();

                // Links.
                for (size_t i = 0; i < current_zone->expected_elements_count; ++i)
                {
                    getline(f, line);
                    get_zone_links_from_string<TEdgeData>(mesh, current_zone, line, i);
                }
            }
        }

        f.close();

        // Init global identifiers.
        mesh.init_global_identifiers();

        // Distribute edges between zones.
        mesh.distribute_edges_between_zones();

        // Init neighbourhoods.
        mesh.init_cells_neighbourhoods();

        // Geometry.
        mesh.initial_calc_geometry();

        return true;
    }

    /// \brief Load mesh with no additional data.
    ///
    /// \param[in,out] mesh                     Mesh to be loaded.
    /// \param[in]     fn                       Name of file.
    ///
    /// \return
    /// true - if loading is complete,
    /// false - otherwise.
    static bool
    load_mesh(Mesh& mesh,
              const string& fn)
    {
        return load_mesh<NodeDataStub,
                         NodeDataElementStub,
                         EdgeDataStub,
                         CellDataStub,
                         CellDataElementStub>(mesh,
                                              fn,
                                              NodeDataElementStubMapper,
                                              CellDataElementStubMapper);
    }

    /// \brief Store zone data.
    ///
    /// Store zone data.
    ///
    /// \tparam    TNodeData                Node data.
    /// \tparam    TNodeDataElement         Node data mapper.
    /// \tparam    TCellData                Cell data.
    /// \tparam    TCellDataElement         Cell data mapper.
    /// \param[in] zone                     Zone.
    /// \param[in] variables_names          Names of variables.
    /// \param[in] varlocation_cellcentered Position of cellcentered data.
    /// \param[in] f                        File stream.
    /// \param[in] node_data_element_mapper Mapper for node data.
    /// \param[in] cell_data_element_mapper Mapper for cell data.
    template<typename TNodeData,
             typename TNodeDataElement,
             typename TCellData,
             typename TCellDataElement>
    static void
    store_zone_data(Zone* zone,
                    const vector<string>& variables_names,
                    const pair<size_t, size_t>& varlocation_cellcentered,
                    ofstream& f,
                    utils::Mapper<TNodeDataElement>& node_data_element_mapper,
                    utils::Mapper<TCellDataElement>& cell_data_element_mapper)
    {
        f.precision(17);

        // Checkers.
        DEBUG_CHECK_ERROR(variables_names[0] == "X", "first variable must be X");
        DEBUG_CHECK_ERROR(variables_names[1] == "Y", "second variable must be Y");
        DEBUG_CHECK_ERROR(variables_names[2] == "Z", "third variable must be Z");
        DEBUG_CHECK_ERROR(variables_names.size() == varlocation_cellcentered.second,
                          "wrong varlocation cellcentered for storing data")

        // First element is X.
        for (size_t i = 0; i < zone->nodes_count(); ++i)
        {
            f << zone->node(i)->point().x << " ";
        }
        f << endl;

        // Second element is Y.
        for (size_t i = 0; i < zone->nodes_count(); ++i)
        {
            f << zone->node(i)->point().y << " ";
        }
        f << endl;

        // Third element is Z.
        for (size_t i = 0; i < zone->nodes_count(); ++i)
        {
            f << zone->node(i)->point().z << " ";
        }
        f << endl;

        // Data elements of nodes.
        for (size_t v = 3; v < varlocation_cellcentered.first - 1; ++v)
        {
            string name { variables_names[v] };
            int index = NodeElementMapper.has(name)
                        ? static_cast<int>(NodeElementMapper.get_enum(name))
                        : static_cast<int>(node_data_element_mapper.get_enum(name));

            for (size_t i = 0; i < zone->nodes_count(); ++i)
            {
                f << zone->node(i)->get_element<TNodeData>(index) << " ";
            }

            f << endl;
        }

        // Data elements of cells.
        for (size_t v = varlocation_cellcentered.first - 1;
             v < varlocation_cellcentered.second;
            ++v)
        {
            string name { variables_names[v] };
            int index = CellElementMapper.has(name)
                        ? static_cast<int>(CellElementMapper.get_enum(name))
                        : static_cast<int>(cell_data_element_mapper.get_enum(name));

            for (size_t i = 0; i < zone->cells_count(); ++i)
            {
                f << zone->cell(i)->get_element<TCellData>(index) << " ";
            }

            f << endl;
        }
    }

    /// \brief Store mesh.
    ///
    /// \tparam    TNodeData                Node data.
    /// \tparam    TNodeDataElement         Node data mapper.
    /// \tparam    TCellData                Cell data.
    /// \tparam    TCellDataElement         Cell data mapper.
    /// \param[in] mesh                     Mesh to be stored.
    /// \param[in] variables_names          List of variables names to store.
    /// \param[in] varlocation_cellcentered Position of cellcentered data.
    /// \param[in] fn                       Name of file.
    /// \param[in] node_data_element_mapper Mapper for node data.
    /// \param[in] cell_data_element_mapper Mapper for cell data.
    ///
    /// \return
    /// true - if store is complete,
    /// false - otherwise.
    template<typename TNodeData,
             typename TNodeDataElement,
             typename TCellData,
             typename TCellDataElement>
    static bool
    store_mesh(Mesh& mesh,
               const vector<string>& variables_names,
               const pair<size_t, size_t>& varlocation_cellcentered,
               const string& fn,
               utils::Mapper<TNodeDataElement>& node_data_element_mapper,
               utils::Mapper<TCellDataElement>& cell_data_element_mapper)
    {
        if (variables_names.empty())
        {
            return store_mesh<TNodeData,
                              TNodeDataElement,
                              TCellData,
                              TCellDataElement>(mesh,
                                                fn,
                                                node_data_element_mapper,
                                                cell_data_element_mapper);
        }

        ofstream f(fn);

        if (!f.is_open())
        {
            return false;
        }

        // First line is comment with name of program.
        f << "# crys export" << endl;

        // Title line.
        f << "TITLE=\"" << mesh.title << "\"" << endl;

        // Variables line.
        store_mesh_variables_names(variables_names, f);

        // Store all zones.
        for (size_t i = 0; i < mesh.zones_count(); ++i)
        {
            Zone* current_zone = mesh.get_zones()[i];

            // Zone name line.
            f << "ZONE T=\"" << current_zone->name << "\"" << endl;

            // Nodes count line.
            f << "NODES=" << current_zone->nodes_count() << endl;

            // Elements count line.
            f << "ELEMENTS=" << current_zone->cells_count() << endl;

            // Datapacking line.
            f << "DATAPACKING=BLOCK" << endl;

            // Zone type line.
            f << "ZONETYPE=FETRIANGLE" << endl;

            // Varlocation line.
            f << "VARLOCATION=(["
              << varlocation_cellcentered.first << "-"
             << varlocation_cellcentered.second << "]=CELLCENTERED)" << endl;

            // Store all data.
            store_zone_data<TNodeData,
                            TNodeDataElement,
                            TCellData,
                            TCellDataElement>(current_zone,
                                              variables_names,
                                              varlocation_cellcentered,
                                              f,
                                              node_data_element_mapper,
                                              cell_data_element_mapper);

            // Store links.
            store_zone_links(current_zone, f);
        }

        f.close();

        return true;
    }

    /// \brief Store mesh.
    ///
    /// \tparam    TNodeData                Node data.
    /// \tparam    TNodeDataElement         Node data mapper.
    /// \tparam    TCellData                Cell data.
    /// \tparam    TCellDataElement         Cell data mapper.
    /// \param[in] mesh                     Mesh to be stored.
    /// \param[in] fn                       Name of file.
    /// \param[in] node_data_element_mapper Mapper for node data.
    /// \param[in] cell_data_element_mapper Mapper for cell data.
    ///
    /// \return
    /// true - if store is complete,
    /// false - otherwise.
    template<typename TNodeData,
             typename TNodeDataElement,
             typename TCellData,
             typename TCellDataElement>
    static bool
    store_mesh(Mesh& mesh,
               const string& fn,
               utils::Mapper<TNodeDataElement>& node_data_element_mapper,
               utils::Mapper<TCellDataElement>& cell_data_element_mapper)
    {
        return store_mesh<TNodeData,
                          TNodeDataElement,
                          TCellData,
                          TCellDataElement>(mesh,
                                            mesh.variables_names,
                                            mesh.varlocation_cellcentered,
                                            fn,
                                            node_data_element_mapper,
                                            cell_data_element_mapper);
    }

    /// \brief Store mesh with no additional data.
    ///
    /// \param[in] mesh                     Mesh to be stored.
    /// \param[in] fn                       Name of file.
    ///
    /// \return
    /// true - if store is complete,
    /// false - otherwise.
    static bool
    store_mesh(Mesh& mesh,
               const string& fn)
    {
        return store_mesh<NodeDataStub,
                          NodeDataElementStub,
                          CellDataStub,
                          CellDataElementStub>(mesh,
                                               fn,
                                               NodeDataElementStubMapper,
                                               CellDataElementStubMapper);
    }

    // Export STL.
    static void
    export_stl(Mesh& mesh,
               const string& fn);

private:

    // Get mesh title from string.
    static void
    get_mesh_title_from_string(Mesh& mesh,
                               const string& s);

    // Get mesh variables names from string.
    static void
    get_mesh_variables_names_from_string(Mesh& mesh,
                                         const string& s);

    // Store mesh variables names.
    static void
    store_mesh_variables_names(const vector<string>& variables_names,
                               ofstream& f);

    // Get zone name from string.
    static void
    get_zone_name_from_string(Zone* zone,
                              const string& s);

    // Get zone nodes count from string.
    static void
    get_zone_nodes_count_from_string(Zone* zone,
                                     const string& s);

    // Get zone elements count from string.
    static void
    get_zone_elements_count_from_string(Zone* zone,
                                        const string& s);

    // Get zone varlocation from string.
    static void
    get_zone_varlocation_cellcentered_from_string(Mesh& mesh,
                                                  const string& s);

    // Get zone data from string.
    static void
    get_zone_data_from_string(vector<vector<double>>& data,
                              const string& s);

    // Link node and edge.
    static void
    link_node_edge(Node* n,
                   Edge* e);

    // Link node and cell.
    static void
    link_node_cell(Node* n,
                   Cell* c);

    // Link edge and cell.
    static void
    link_edge_cell(Edge* e,
                   Cell* c);

    // Store zone links.
    static void
    store_zone_links(Zone* zone,
                     ofstream& f);
};

/// @}

}

}

#endif // MESH_FILER_H
