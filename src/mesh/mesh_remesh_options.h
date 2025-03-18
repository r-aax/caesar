/// \file
/// \brief Remesh options declaration.
///
/// Remesh options declaration.

#ifndef CAESAR_MESH_REMESH_OPTIONS_H
#define CAESAR_MESH_REMESH_OPTIONS_H

#include "mesh_remesh_method.h"

#include <iostream>

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Options for remesher.
///
/// Options may only be initialized and have get methods.
class RemeshOptions
{
    friend class Remesher;

private:

    /// \brief Remesh method.
    RemeshMethod method { RemeshMethod::Prisms };

    /// \brief Height if ice we decide as zero (m).
    double hi_as_zero_threshold { 0.0001 };

    /// \brief Minimum number of steps for remesh.
    int nsteps_min { 1 };

    /// \brief Maximim number of steps for remesh.
    int nsteps_max { 10 };

    /// \brief Maximum permitted value of quality for remeshing (no unit of measure).
    ///
    /// Maximum permitted value of coefficient which is calculated as
    /// height of ice on one iteration of remeshing divided by shortest side of cell.
    double nsteps_hi_side_fact { 0.1 };

    /// \brief Maximum part of bad cells which can be ignored.
    double nsteps_ignore_part { 0.05 };

    /// \brief Normals smoothing iterations count.
    int nsmooth_steps { 0 };

    /// \brief Parameter for normals smoothing.
    double nsmooth_s { 10.0 };

    /// \brief Parameter for normals smoothing.
    double nsmooth_k { 0.15 };

    /// \brief Heights smoothing iterations count.
    int hsmooth_steps { 0 };

    /// \brief Parameter for heights smoothing.
    double hsmooth_alfa { 0.2 };

    /// \brief Parameter for heights smoothing.
    double hsmooth_beta { 0.1 };

    /// \brief Null-space smoothing iterations count.
    int nss_steps { 0 };

    /// \brief Parameter of smoothing in null-space.
    double nss_epsilon { 0.01 };

    /// \brief Parameter of moving nodes while null-space smoothing.
    double nss_st { 0.2 };

public:

    /// \brief Default constrructor.
    ///
    /// Default constructor. All options set to default values.
    RemeshOptions()
    {
    }

    // Set all options in the same time.
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
        double nss_st_);

private:

    /// \brief Get remesh method.
    ///
    /// Get remesh method.
    ///
    /// \return
    /// Remesh method.
    inline RemeshMethod
    get_method() const
    {
        return method;
    }

    /// \brief Get height if ice we decide as zero (m).
    ///
    /// Get height if ice we decide as zero (m).
    ///
    /// \return
    /// Height if ice we decide as zero (m).
    inline double
    get_hi_as_zero_threshold() const
    {
        return hi_as_zero_threshold;
    }

    /// \brief Get minimum number of steps for remesh.
    ///
    /// Get minimum number of steps for remesh.
    ///
    /// \return
    /// Minimum number of steps for remesh.
    inline int
    get_nsteps_min() const
    {
        return nsteps_min;
    }

    /// \brief Get maximim number of steps for remesh.
    ///
    /// Get maximim number of steps for remesh.
    ///
    /// \return
    /// Maximim number of steps for remesh.
    inline int
    get_nsteps_max() const
    {
        return nsteps_max;
    }

    /// \brief Get maximum permitted value of quality for remeshing (no unit of measure).
    ///
    /// Get maximum permitted value of quality for remeshing (no unit of measure).
    ///
    /// \return
    /// Maximum permitted value of quality for remeshing (no unit of measure).
    inline double
    get_nsteps_hi_side_fact() const
    {
        return nsteps_hi_side_fact;
    }

    /// \brief Get maximum part of bad cells which can be ignored.
    ///
    /// Get maximum part of bad cells which can be ignored.
    ///
    /// \return
    /// Maximum part of bad cells which can be ignored.
    inline double
    get_nsteps_ignore_part() const
    {
        return nsteps_ignore_part;
    }

    /// \brief Get normals smoothing iterations count.
    ///
    /// Get normals smoothing iterations count.
    ///
    /// \return
    /// Normals smoothing iterations count.
    inline int
    get_nsmooth_steps() const
    {
        return nsmooth_steps;
    }

    /// \brief Get parameter for normals smoothing.
    ///
    /// Get parameter for normals smoothing.
    ///
    /// \return
    /// Parameter for normals smoothing.
    inline double
    get_nsmooth_s() const
    {
        return nsmooth_s;
    }

    /// \brief Get parameter for normals smoothing.
    ///
    /// Get parameter for normals smoothing.
    ///
    /// \return
    /// Parameter for normals smoothing.
    inline double
    get_nsmooth_k() const
    {
        return nsmooth_k;
    }

    /// \brief Get heights smoothing iterations count.
    ///
    /// Get heights smoothing iterations count.
    ///
    /// \return
    /// Heights smoothing iterations count.
    inline int
    get_hsmooth_steps() const
    {
        return hsmooth_steps;
    }

    /// \brief Get parameter for heights smoothing.
    ///
    /// Get parameter for heights smoothing.
    ///
    /// \return
    /// Parameter for heights smoothing.
    inline double
    get_hsmooth_alfa() const
    {
        return hsmooth_alfa;
    }

    /// \brief Get parameter for heights smoothing.
    ///
    /// Get parameter for heights smoothing.
    ///
    /// \return
    /// Parameter for heights smoothing.
    inline double
    get_hsmooth_beta() const
    {
        return hsmooth_beta;
    }

    /// \brief Get null-space smoothing iterations count.
    ///
    /// Get null-space smoothing iterations count.
    ///
    /// \return
    /// Null-space smoothing iterations count.
    inline int
    get_nss_steps() const
    {
        return nss_steps;
    }

    /// \brief Get parameter of smoothing in null-space.
    ///
    /// Get parameter of smoothing in null-space.
    ///
    /// \return
    /// Parameter of smoothing in null-space.
    inline double
    get_nss_epsilon() const
    {
        return nss_epsilon;
    }

    /// \brief Get parameter of moving nodes while null-space smoothing.
    ///
    /// Get parameter of moving nodes while null-space smoothing.
    ///
    /// \return
    /// Parameter of moving nodes while null-space smoothing.
    inline double
    get_nss_st() const
    {
        return nss_st;
    }

public:

    // Print function.
    friend std::ostream&
    operator<<(std::ostream& os,
               const RemeshOptions& x);
};

/// @}

}

}

#endif // !CAESAR_MESH_REMESH_OPTIONS_H
