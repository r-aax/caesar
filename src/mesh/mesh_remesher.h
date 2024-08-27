/// \file
/// \brief Remesher.
///
/// Remesher declaration.

#ifndef MESH_REMESHER_H
#define MESH_REMESHER_H

#include "mesh_mesh.h"
#include "mesh_remesh_method.h"
#include "mesh_remesh_options.h"

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Remesher class.
class Remesher
{

private:

    //
    // Common functions.
    //

    // Zero all ice.
    static void
    zero_ice(Mesh& mesh);

    // Zero small accounts of ice in mesh cells.
    static void
    zero_ice_below_threshold(Mesh& mesh,
                             double thr);

    // Steps of remeshing based on height of ice.
    static int
    remeshing_nsteps(Mesh& mesh,
                     const RemeshOptions& opts);

    //
    // Prisms remeshing.
    //

    // Remesh with prizm method.
    static void
    remesh_prisms(Mesh& mesh,
                  const RemeshOptions& opts);

    //
    // Tong remeshing methods.
    //

    // Init target, rest ice.
    static void
    init_target_rest_ice(Mesh& mesh);

    // Calc ice chunks.
    static void
    calc_ice_chunks(Mesh& mesh,
                    int rest_iterations);

    // Init nodes and cells ice directions.
    static void
    init_ice_dirs(Mesh& mesh);

    // Smooth normals.
    static void
    normals_smoothing(Mesh& mesh,
                      const RemeshOptions& opts);

    // Define ice shifts.
    static void
    define_ice_shifts(Mesh& mesh);

    // Smoothing heights.
    static void
    heights_smoothing(Mesh& mesh,
                      const RemeshOptions& opts);

    // Move nodes.
    static void
    move_nodes(Mesh& mesh);

    // Calculate laplacian for null-space smoothing.
    static void
    calc_laplacian(Node* node,
                   geom::Vector& dv);

    // Null-space smoothing.
    static void
    null_space_smoothing(Mesh& mesh,
                         const RemeshOptions& opts);

    // Remesh one step with Tong method.
    static void
    remesh_tong_step(Mesh& mesh,
                     const RemeshOptions& opts,
                     int stepi,
                     int steps);

    // Remesh with Tong method.
    static void
    remesh_tong(Mesh& mesh,
                const RemeshOptions& opts);

public:

    //
    // Remesh method.
    //

    // Remesh.
    static void
    remesh(Mesh& mesh,
           const RemeshOptions& opts);
};

/// @}

}

#endif // !MESH_REMESHER_H
