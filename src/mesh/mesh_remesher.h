/// \file
/// \brief Remesher.
///
/// Remesher declaration.

#ifndef CAESAR_MESH_REMESHER_H
#define CAESAR_MESH_REMESHER_H

#include "mesh_mesh.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Remesh method.
///
/// Remesh method.
enum class RemeshMethod
{
    /// \brief First element.
    ///
    /// First element.
    First = 0,

    /// \brief Prisms method.
    ///
    /// Prizms method.
    Prisms = First,

    /// \brief Tong method.
    ///
    /// Tong method.
    Tong,

    /// \brief Last element.
    ///
    /// Last element.
    Last = Tong
};

/// \brief Remesh method mapper.
///
/// Remesh method mapper.
extern utils::Mapper<RemeshMethod> RemeshMethodMapper;

/// \brief Options for remesher.
///
/// Options may only be initialized and have get methods.
struct RemeshOptions
{
    /// \brief Remesh method.
    ///
    /// Remesh method.
    RemeshMethod method { RemeshMethod::Prisms };

    /// \brief Height if ice we decide as zero (m).
    ///
    /// Height if ice we decide as zero (m).
    double hi_as_zero_threshold { 0.0001 };

    /// \brief Minimum number of steps for remesh.
    ///
    /// Minimum number of steps for remesh.
    int nsteps_min { 1 };

    /// \brief Maximim number of steps for remesh.
    ///
    /// Maximim number of steps for remesh.
    int nsteps_max { 10 };

    /// \brief Maximum permitted value of quality for remeshing (no unit of measure).
    ///
    /// Maximum permitted value of coefficient which is calculated as
    /// height of ice on one iteration of remeshing divided by shortest side of cell.
    double nsteps_hi_side_fact { 0.1 };

    /// \brief Maximum part of bad cells which can be ignored.
    ///
    /// Maximum part of bad cells which can be ignored.
    double nsteps_ignore_part { 0.05 };

    /// \brief Normals smoothing iterations count.
    ///
    /// Normals smoothing iterations count.
    int nsmooth_steps { 0 };

    /// \brief Parameter for normals smoothing.
    ///
    /// Parameter for normals smoothing.
    double nsmooth_s { 10.0 };

    /// \brief Parameter for normals smoothing.
    ///
    /// Parameter for normals smoothing.
    double nsmooth_k { 0.15 };

    /// \brief Heights smoothing iterations count.
    ///
    /// Heights smoothing iterations count.
    int hsmooth_steps { 0 };

    /// \brief Parameter for heights smoothing.
    ///
    /// Parameter for heights smoothing.
    double hsmooth_alfa { 0.2 };

    /// \brief Parameter for heights smoothing.
    ///
    /// Parameter for heights smoothing.
    double hsmooth_beta { 0.1 };

    /// \brief Null-space smoothing iterations count.
    ///
    /// Null-space smoothing iterations count.
    int nss_steps { 0 };

    /// \brief Parameter of smoothing in null-space.
    double nss_epsilon { 0.01 };

    /// \brief Parameter of moving nodes while null-space smoothing.
    ///
    /// Parameter of moving nodes while null-space smoothing.
    double nss_st { 0.2 };

    /// \brief Default constrructor.
    ///
    /// Default constructor. All options set to default values.
    RemeshOptions()
    {
    }

    /// \brief Set all options in the same time.
    ///
    /// Set remesh options.
    ///
    /// \param[in] method_               Remesh method.
    /// \param[in] hi_as_zero_threshold_ Zero height threshold.
    /// \param[in] nsteps_min_           Remesh minimum steps count.
    /// \param[in] nsteps_max_           Remesh maximum steps count.
    /// \param[in] nsteps_hi_side_fact_  Minimum value of height / min_side.
    /// \param[in] nsteps_ignore_part_   Part of cells we can ignore while defining steps count.
    /// \param[in] nsmooth_steps_        Normals smooth steps count.
    /// \param[in] nsmooth_s_            Normals smooth parameter.
    /// \param[in] nsmooth_k_            Normals smooth parameter.
    /// \param[in] hsmooth_steps_        Heights smooth steps count.
    /// \param[in] hsmooth_alfa_         Heights smooth parameter.
    /// \param[in] hsmooth_beta_         Heights smooth parameter.
    /// \param[in] nss_steps_            Null-space smooth steps count.
    /// \param[in] nss_epsilon_          Null-space smooth parameter.
    /// \param[in] nss_st_               Null-space smooth parameter.
    void
    set(RemeshMethod method_,
        double hi_as_zero_threshold_,
        int nsteps_min_,
        int nsteps_max_,
        double nsteps_hi_side_fact_,
        double nsteps_ignore_part_,
        int nsmooth_steps_,
        double nsmooth_s_,
        double nsmooth_k_,
        int hsmooth_steps_,
        double hsmooth_alfa_,
        double hsmooth_beta_,
        int nss_steps_,
        double nss_epsilon_,
        double nss_st_)
    {
        method = method_;
        hi_as_zero_threshold = hi_as_zero_threshold_;
        nsteps_min = nsteps_min_;
        nsteps_max = nsteps_max_;
        nsteps_hi_side_fact = nsteps_hi_side_fact_;
        nsteps_ignore_part = nsteps_ignore_part_;
        nsmooth_steps = nsmooth_steps_;
        nsmooth_s = nsmooth_s_;
        nsmooth_k = nsmooth_k_;
        hsmooth_steps = hsmooth_steps_;
        hsmooth_alfa = hsmooth_alfa_;
        hsmooth_beta = hsmooth_beta_;
        nss_steps = nss_steps_;
        nss_epsilon = nss_epsilon_;
        nss_st = nss_st_;
    }

    /// \brief Print function.
    ///
    /// Print options to stream.
    ///
    /// \param[in] os Output stream.
    /// \param[in] x  Options.
    friend std::ostream&
    operator<<(std::ostream& os,
               const RemeshOptions& x)
    {
        os << "remesh:" << RemeshMethodMapper.name(x.method)
           << ", zero_thr:" << x.hi_as_zero_threshold
           << ", nsteps:[" << x.nsteps_min << "," << x.nsteps_max << "]/"
                           << x.nsteps_hi_side_fact << "/" << x.nsteps_ignore_part
           << ", nsmooth:" << x.nsmooth_steps << "/" << x.nsmooth_s << "/" << x.nsmooth_k
           << ", hsmooth:" << x.hsmooth_steps << "/" << x.hsmooth_alfa << "/" << x.hsmooth_beta
           << ", nss_smooth:" << x.nss_steps << "/" << x.nss_epsilon << "/" << x.nss_st;

        return os;
    }
};

/// \brief Remesher class.
///
/// Remesher class.
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

}

#endif // !CAESAR_MESH_REMESHER_H
