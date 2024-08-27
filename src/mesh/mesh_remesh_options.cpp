/// \file
/// \brief Remesh options implementation.
///
/// Remesh options implementation.

#include "mesh_remesh_options.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

// Set all options in the same time.
void
RemeshOptions::set(RemeshMethod method_,
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
ostream&
operator<<(ostream& os,
           const RemeshOptions& x)
{
    os << "remesh:" << RemeshMethodMapper.get_name(x.get_method())
       << ", zero_thr:" << x.get_hi_as_zero_threshold()
       << ", nsteps:[" << x.get_nsteps_min()
                       << "," << x.get_nsteps_max()
                       << "]/" << x.get_nsteps_hi_side_fact()
                       << "/" << x.get_nsteps_ignore_part()
       << ", nsmooth:" << x.get_nsmooth_steps()
                       << "/" << x.get_nsmooth_s()
                       << "/" << x.get_nsmooth_k()
       << ", hsmooth:" << x.get_hsmooth_steps()
                       << "/" << x.get_hsmooth_alfa()
                       << "/" << x.get_hsmooth_beta()
       << ", nss_smooth:" << x.get_nss_steps()
                          << "/" << x.get_nss_epsilon()
                          << "/" << x.get_nss_st();

    return os;
}

/// @}

}

}
