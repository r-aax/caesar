/// \file
/// \brief Decomposer implementation.
///
/// Mesh decomposer implementation.

#include "mesh_decomposer.h"

#include <deque>

#include "parl/parl.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Mesh decomposition type mapper.
///
/// Mesh decomposition type mapper.
utils::Mapper<DecompositionType> MeshDecompositionTypeMapper
{
    "mesh decomposition type",
    vector<string> { "NO", "RANDOM", "LINEAR", "FARHAT" }
};

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
    DEBUG_CHECK_ERROR(hi < mesh.all.cells_count(), "wrong higher bound of cells diapason");

    for (size_t i = lo; i <= hi; ++i)
    {
        mesh.all.cell(i)->domain = domain;
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
    size_t cc { mesh.all.cells_count() };

    for (size_t i = 0; i < cc; ++i)
    {
        Cell* c { mesh.all.cell(i) };

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
    size_t cc { mesh.all.cells_count() };

    for (size_t i = 0; i < cc; ++i)
    {
        Cell* c { mesh.all.cell(i) };

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
    size_t n = mesh.all.cells_count();
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

/// \brief Farhat decomposition.
///
/// Farhat decomposition.
///
/// \param[out] mesh Mesh,
/// \param[in]  dn   Number of domains.
void
Decomposer::decompose_farhat(Mesh& mesh,
                             size_t dn)
{
    size_t n { mesh.all.cells_count() };
    size_t cnt { n / dn }, r { n % dn };

    // Remove all cell marks.
    mesh.mark_cells([](Cell* c) { (void)c; return false; });

    //
    // Now we have to walk mesh in width.
    //

    // Queue of cells for walk.
    deque<Cell*> q;

    // Current domain.
    size_t cur_domain { 0 };

    // Current count of elements in domain.
    size_t cur_cnt { (cur_domain < r) ? (cnt + 1) : cnt };

    // Walked cells count.
    size_t walked_cells { 0 };

    // Get 0-th cell of the mesh and put it into the queue.
    Cell* c { mesh.all.cells()[0] };
    c->set_mark(1);
    q.push_back(c);

    // Walk.
    while (!q.empty())
    {
        Cell* c { q.front() };
        size_t ec { c->edges_count() };

        q.pop_front();
        ++walked_cells;
        c->domain = cur_domain;
        --cur_cnt;

        // Check domain change.
        if (cur_cnt == 0)
        {
            ++cur_domain;
            cur_cnt = (cur_domain < r) ? (cnt + 1) : cnt;
        }

        // Check all neighbours.
        for (size_t i = 0; i < ec; ++i)
        {
            Edge* e { c->edge(i) };
            Cell* nc { c->get_neighbour(e) };

            if (nc && (nc->get_mark() == 0))
            {
                nc->set_mark(1);
                q.push_back(nc);
            }
        }
    }

    CHECK_ERROR(walked_cells == mesh.all.cells_count(),
                "there are missed cells while Farhat decomposition algorithm");

    // Remove all cell marks.
    mesh.mark_cells([](Cell* c) { (void)c; return false; });
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
    size_t ec { mesh.all.edges_count() }, cc { mesh.all.cells_count() };

    // Clear old vectors.
    mesh.own.clear_cells();

    // Domains cells is matrix.
    mesh.domains_cells.resize(s);

    // Fill domain cells and own cells.
    for (size_t i = 0; i < cc; ++i)
    {
        Cell* c { mesh.all.cell(i) };
        size_t d = c->get_domain();

        if (d == r)
        {
            mesh.own.add_cell(c);
        }

        mesh.domains_cells[d].push_back(c);
    }

    // Fill own edges list.
    for (size_t i = 0; i < ec; ++i)
    {
        Edge* e { mesh.all.edge(i) };
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
            mesh.own.add_edge(e);
        }
    }

    // Allocate boundaries.
    mesh.boundaries.allocate();

    // Process boundary cells.
    for (size_t i = 0; i < ec; ++i)
    {
        Edge* e { mesh.all.edge(i) };

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
            DEBUG_CHECK_ERROR(dn == 1,
                              "it is needed to perform decomposition for domains count "
                              + to_string(dn));
            decompose_no(mesh);
            break;

        case DecompositionType::Random:
            decompose_random(mesh, dn);
            break;

        case DecompositionType::Linear:
            decompose_linear(mesh, dn);
            break;

        case DecompositionType::Farhat:
            decompose_farhat(mesh, dn);
            break;

        default:
            DEBUG_ERROR("unexpected mesh decomposition type");
    }

    // Post decompose (only if processes count is equal to domains count).
    if (parl::mpi_size() == dn)
    {
        post_decompose(mesh);
    }
}

/// @}

}

}
