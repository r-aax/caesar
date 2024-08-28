/// \file
/// \brief Decomposer implementation.
///
/// Mesh decomposer implementation.

#include "mesh_decomposer.h"

#include "parl/parl.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \breif Set domain number to cells diapason.
///
/// Set domain number to cells diapason.
///
/// \param[out] mesh   Mesh.
/// \param[in]  lo     Lower bound of diapason.
/// \param[in]  hi     Higher bound of diapason.
/// \param[in]  domain Domain number.
void
Decomposer::set_cells_diapason_with_domain(Mesh& mesh,
                                           size_t lo,
                                           size_t hi,
                                           size_t domain)
{
    DEBUG_CHECK_ERROR(lo <= hi, "wrong cells diapason");
    DEBUG_CHECK_ERROR(hi < mesh.cells.size(), "wrong higher bound of cells diapason");

    for (size_t i = lo; i <= hi; ++i)
    {
        mesh.cells[i]->domain = domain;
    }
}

/// \brief Decompose with type NO.
///
/// Decompose mesh with type NO.
///
/// \param[out] mesh Mesh.
void
Decomposer::decompose_no(Mesh& mesh)
{
    for (auto c : mesh.cells)
    {
        c->domain = 0;
    }
}

/// \brief Random decomposition.
///
/// Decomposition with type RANDOM.
///
/// \param[out] mesh Mesh,
/// \param[in]  dn   Number of domains.
void
Decomposer::decompose_random(Mesh& mesh,
                             size_t dn)
{
    for (auto c : mesh.cells)
    {
        c->domain = static_cast<size_t>(mth::randint(0, static_cast<int>(dn) - 1));
    }
}

/// \brief Linear decomposition.
///
/// Linear decomposition.
///
/// \param[out] mesh Mesh,
/// \param[in]  dn   Number of domains.
void
Decomposer::decompose_linear(Mesh& mesh,
                             size_t dn)
{
    size_t n = mesh.cells.size();
    size_t lo = 0, hi = 0;
    size_t cnt = n / dn, r = n % dn;

    for (size_t i = 0; i < dn; ++i)
    {
        size_t cur_cnt = (i < r) ? (cnt + 1) : cnt;

        hi = lo + cur_cnt - 1;
        set_cells_diapason_with_domain(mesh, lo, hi, i);
        lo = hi + 1;
    }

    DEBUG_CHECK_ERROR(lo == n, "cells balance error while linear decomposition");
}

/// \brief Post decompose action.
///
/// 1. Form boundaries for all other domains.
/// 2. Init vectors of own cells and ext cells.
///
/// \param[out] mesh Mesh.
void
Decomposer::post_decompose(Mesh& mesh)
{
    size_t s = parl::mpi_size();
    size_t r = parl::mpi_rank();

    // Clear old vectors.
    mesh.own_cells.clear();

    // Domains cells is matrix.
    mesh.domains_cells.resize(s);

    // Fill domain cells and own cells.
    for (auto c : mesh.cells)
    {
        size_t d = c->get_domain();

        if (d == r)
        {
            mesh.own_cells.push_back(c);
        }

        mesh.domains_cells[d].push_back(c);
    }

    // Fill own edges list.
    for (auto e : mesh.edges)
    {
        bool is_own { false };

        if ((e->cells_count() > 0) && (e->domain_0() == r))
        {
            is_own = true;
        }

        if ((e->cells_count() > 1) && (e->domain_1() == r))
        {
            is_own = true;
        }

        if (is_own)
        {
            mesh.own_edges.push_back(e);
        }
    }

    // Allocate boundaries.
    mesh.boundaries.allocate();

    // Process boundary cells.
    for (auto e : mesh.edges)
    {
        if (e->is_cross())
        {
            size_t d0 = e->domain_0(), d1 = e->domain_1();

            if (d0 == r)
            {
                // d1 - neighbour domain, c1 - ghost cell.
                mesh.boundaries.add(d1, e->cell(0), e->cell(1));
            }
            else if (d1 == r)
            {
                // d0 - neighbour domain, c0 - ghost cell.
                mesh.boundaries.add(d0, e->cell(1), e->cell(0));
            }
        }
    }

    // Transfer sizes.
    mesh.boundaries.set_buffers_sizes();

    // Allocate gatherer for gather data in process 0.
    mesh.gatherer.allocate();

    // Allocate size for all gather buffers.
    for (size_t i = 1; i < s; ++i)
    {
        mesh.gatherer.set_size(i, mesh.domains_cells[i].size());
    }

    // Init local identifiers.
    mesh.init_local_identifiers();
}

/// \brief Decompose mesh.
///
/// Decompose mesh.
///
/// \param[out] mesh Mesh.
/// \param[in]  type Decomposition type.
/// \param[in]  dn   Number of domains.
void
Decomposer::decompose(Mesh& mesh,
                      DecompositionType type,
                      size_t dn)
{
    switch (type)
    {
        case DecompositionType::No:

            DEBUG_CHECK_ERROR(dn == 1, "it is needed to perform decomposition for domains count " + to_string(dn));

            decompose_no(mesh);

            break;

        case DecompositionType::Random:

            decompose_random(mesh, dn);

            break;

        case DecompositionType::Linear:

            decompose_linear(mesh, dn);

            break;

        default:
            DEBUG_ERROR("unexpected mesh decomposition type");
    }

    // Post decompose.
    post_decompose(mesh);
}

/// @}

}

}
