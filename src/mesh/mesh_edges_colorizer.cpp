/// \file
/// \brief Implementation of mesh edges colorization.
///
/// Implementation of mesh edges colorizer.

#include "mesh_edges_colorizer.h"
#include "graph/graph.h"

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Colorize edges.
///
/// Set colors to edges.
///
/// \param[in,out] mesh Mesh.
void
EdgesColorizer::colorize_edges(Mesh& mesh)
{
    graph::Graph* g = graph::GraphFactory::create_edgeless_graph(mesh.own_cells_count());
    vector<Edge*>& mesh_own_edges { mesh.get_own_edges() };

    // Add all edges.
    for (auto e : mesh_own_edges)
    {
        DEBUG_CHECK_ERROR(e->cells_count() > 0, "mesh edge without cells is detected");

        if (e->cells_count() > 1)
        {
            // Inner edge.
            g->add_edge(static_cast<size_t>(e->cell_0()->get_loc_id()),
                        static_cast<size_t>(e->cell_1()->get_loc_id()));
        }
        else
        {
            // Edge, one of incident cells of which is not own cell.
            // Add new vertex for this outer cell.

            graph::Vertex* v = g->new_vertex();

            // Now add new edge.
            g->add_edge(static_cast<size_t>(e->cell_0()->get_loc_id()),
                        static_cast<size_t>(v->get_id()));
        }
    }

    // Edges coloring.
    g->edges_coloring_greedy();

    // Pass edges colors to mesh edges.
    // Simultaneously we build colors histogramm
    // and split vector of edges into vectors of
    // monochromic edges vectors.
    for (size_t i = 0; i < g->size(); ++i)
    {
        int color = g->get_edge(i)->get_color();

        mesh.register_edge_color(mesh_own_edges[i], color);
    }

    DEBUG_CHECK_ERROR(mesh.is_own_edges_colors_distribution_correct(),
                      "wrong own edges colors distribution");

    delete g;
}

/// @}

}
