/// \file
/// \brief Remesher implementation.
///
/// Remesher implementation.
///
/// source for Tong algorithm:
/// Tong X., Thompson D., Arnoldus Q., Collins E., Luke E.
/// Three-dimensional surface evolution and mesh deformation for aircraft icing applications.

#include "mesh_remesher.h"

#include "utils/utils.h"
#include "mth/mth.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

//
// Common functions.
//

/// \brief Zero all ice.
///
/// Zero all ice.
///
/// \param[in,out] mesh Mesh.
void
Remesher::zero_ice(Mesh& mesh)
{
    #pragma omp parallel for
    for (auto c : mesh.cells)
    {
        c->ice_shift = 0.0;
    }
}

/// \brief Zero small accounts of ice in mesh cells.
///
/// Zero ice in cells if it is below the threshold.
///
/// \param[in,out] mesh Mesh.
/// \param[in]     thr  Threshold.
void
Remesher::zero_ice_below_threshold(Mesh& mesh,
                                   double thr)
{
    #pragma omp parallel for
    for (auto c : mesh.cells)
    {
        if (c->ice_shift < thr)
        {
            c->ice_shift = 0.0;
        }
    }
}

/// \brief Steps of remeshing based on height of ice.
///
/// Remesh uses multi-layer ice growth ideology.
///
/// source:
/// Bourgault-Cote S., Hasanzadeh K., Lavoie P., Laurendeau.
/// Multi-layer icing methodologies for conservative ice growth.
///
/// \param[in] mesh Mesh.
/// \param[in] opts Options.
///
/// \return
/// Count of steps for remesh.
int
Remesher::remeshing_nsteps(Mesh& mesh,
                           const RemeshOptions& opts)
{
    vector<int> ns;
    double f { opts.get_nsteps_hi_side_fact() };

    // Form vector of iterations number for all cells.
    for (auto c : mesh.cells)
    {
        double min_side = geom::Vector::triangle_min_side_length(c->node(0)->point,
                                                                 c->node(1)->point,
                                                                 c->node(2)->point);

        ns.push_back(static_cast<int>(c->ice_shift / (min_side * f)) + 1);
    }

    // Sort list of iterations number.
    sort(ns.begin(), ns.end(), [] (int a, int b) { return a > b; });

    // Calculate how much cells we can ignore.
    size_t may_ignore = static_cast<size_t>(static_cast<double>(ns.size())
                                            * opts.get_nsteps_ignore_part());

    // Set number of iterations in maximum.
    int n { opts.get_nsteps_max() };

    // Check for ignored part of array.
    if (ns[may_ignore] > n)
    {
        WARNING("ignoring bad faces did not help while remeshing :"
                " remesh_nsteps_max = " + to_string(n)
                + ", first value after ignoring = " + to_string(ns[may_ignore]));
    }
    else
    {
        // Ignoring helped, find correct position.
        for (auto v : ns)
        {
            if (v <= n)
            {
                n = v;

                break;
            }
        }
    }

    return max(n, opts.get_nsteps_min());
}

//
// Prisms remeshing.
//

/// \brief Remesh with prizm method.
///
/// \param[in,out] mesh Mesh.
/// \param[in]     opts Options.
void
Remesher::remesh_prisms(Mesh& mesh,
                        const RemeshOptions& opts)
{
    zero_ice_below_threshold(mesh, opts.get_hi_as_zero_threshold());

    int steps = remeshing_nsteps(mesh, opts);

    // Init ice chunks and zero ice height.
    #pragma omp parallel for
    for (auto c : mesh.cells)
    {
        c->ice_chunk = c->area * c->ice_shift / steps;
        c->ice_shift = 0.0;
    }

    // Provide all steps.
    for (int i = 0; i < steps; ++i)
    {
        // Calculate ice shifts for cells.
        #pragma omp parallel for
        for (auto c : mesh.cells)
        {
            c->ice_shift = c->ice_chunk / c->area;
        }

        // Move nodes.
        #pragma omp parallel for
        for (auto n : mesh.nodes)
        {
            double ice_shift = 0.0;

            for (auto c : n->cells())
            {
                ice_shift += c->ice_shift;
            }

            ice_shift /= static_cast<double>(n->cells_count());

            // Move node.
            geom::Vector::fma(n->normal, ice_shift, n->point, n->point);
        }

        mesh.update_geometry();
    }
}

//
// Tong remeshing.
//

/// \brief Init target, rest ice.
///
/// Init target ice, rest ice ice for each cell.
///
/// \param[in,out] mesh Mesh.
void
Remesher::init_target_rest_ice(Mesh& mesh)
{
    for (auto c : mesh.cells)
    {
        c->target_ice = c->ice_shift * c->area;
        c->rest_ice = c->target_ice;
    }
}

/// \brief Calc ice chunks.
///
/// Calculate ice chunks.
///
/// \param[in,out] mesh            Mesh.
/// \param[in]     rest_iterations Rest iterations.
void
Remesher::calc_ice_chunks(Mesh& mesh,
                          int rest_iterations)
{
    for (auto c : mesh.cells)
    {
        c->ice_chunk = c->rest_ice / rest_iterations;
    }
}

/// \brief Init nodes and cells ice directions.
///
/// Init ice dirs.
///
/// \param[in,out] mesh Mesh.
void
Remesher::init_ice_dirs(Mesh& mesh)
{
    // Cell ice dir it is just its normals.
    for (auto c : mesh.cells)
    {
        c->ice_dir.set(c->normal);
    }

    // Ice dir for node is average of all incident cells ice dirs.
    for (auto n : mesh.nodes)
    {
        n->ice_dir.zero();

        for (auto c : n->cells())
        {
            n->ice_dir.add(c->ice_dir);
        }

        n->ice_dir.normalize();
    }
}

/// \brief Smooth normals.
///
/// Normals smoothing.
///
/// \param[in,out] mesh Mesh.
/// \param[in]     opts Options.
void
Remesher::normals_smoothing(Mesh& mesh,
                            const RemeshOptions& opts)
{
    int steps { opts.get_nsmooth_steps() };
    double s { opts.get_nsmooth_s() };
    double k { opts.get_nsmooth_k() };

    for (int i = 0; i < steps; ++i)
    {
        // Smooth cells' ice directions throught nodes' ice directions.
        for (auto c : mesh.cells)
        {
            geom::Vector new_ice_dir;

            for (auto n : c->nodes())
            {
                double w { max(s * (1.0 - (c->ice_dir * n->ice_dir)), k) };

                geom::Vector::fma(n->ice_dir, w, new_ice_dir, new_ice_dir);
            }

            new_ice_dir.normalize();
            c->ice_dir.set(new_ice_dir);
        }

        // Smooth nodes' ice directions throught cells' ice directions.
        for (auto n : mesh.nodes)
        {
            geom::Vector new_ice_dir;

            for (auto c : n->cells())
            {
                double w { 1.0 / c->area };

                geom::Vector::fma(c->ice_dir, w, new_ice_dir, new_ice_dir);
            }

            new_ice_dir.normalize();
            n->ice_dir.set(new_ice_dir);
        }
    }
}

/// \brief Define ice shifts.
///
/// Define ice shifts.
///
/// \param[in,out] mesh Mesh.
void
Remesher::define_ice_shifts(Mesh& mesh)
{
    static double small_value { 1.0e-10 };

    // Define ice shifts for cells.
    for (auto c : mesh.cells)
    {
        c->ice_shift = c->ice_chunk / c->area;

        // Trying to calculate ice_shift more accurately.
        if (c->ice_chunk > small_value)
        {
            double a { 0.0 }, b { 0.0 }, not_used { 0.0 };

            geom::prismatoid_volume_coefficients(c->node(0)->point,
                                                 c->node(1)->point,
                                                 c->node(2)->point,
                                                 c->node(0)->ice_dir,
                                                 c->node(1)->ice_dir,
                                                 c->node(2)->ice_dir,
                                                 c->normal,
                                                 a, b, not_used);

            if (abs(b) > small_value)
            {
                double d { a * a + 4.0 * b * c->ice_chunk };

                if (d >= 0.0)
                {
                    d = sqrt(d);

                    double h1 { (-a + d) / (2.0 * b) };
                    double h2 { (-a - d) / (2.0 * b) };

                    if ((h1 >= 0.0) && (h2 >= 0.0))
                    {
                        c->ice_shift = min(h1, h2);
                    }
                    else if (h1 >= 0.0)
                    {
                        c->ice_shift = h1;
                    }
                    else if (h2 >= 0.0)
                    {
                        c->ice_shift = h2;
                    }
                }
            }
        }
    }

    // Define ice shifts for all nodes.
    for (auto n : mesh.nodes)
    {
        n->calc_ice_shift();
    }
}

/// \brief Smoothing heights.
///
/// Heights smoothing.
///
/// \param[in,out] mesh Mesh.
/// \param[in]     opts Options.
void
Remesher::heights_smoothing(Mesh& mesh,
                            const RemeshOptions& opts)
{
    int steps { opts.get_hsmooth_steps() };
    double alfa { opts.get_hsmooth_alfa() };
    double beta { opts.get_hsmooth_beta() };

    for (int i = 0; i < steps; ++i)
    {
        double max_h { 0.0 };

        // While redistributing we work with local ice chunks.
        for (auto c : mesh.cells)
        {
            c->loc_ice_chunk = c->ice_chunk;
        }

        // Calculate max h.
        for (auto c : mesh.cells)
        {
            max_h = max(max_h, c->ice_shift);
        }

        // Process all inner edges.
        for (auto e : mesh.edges)
        {
            double mid_area { 0.0 }, delta_v { 0.0 };

            if (!e->is_inner())
            {
                continue;
            }

            Cell* c1 { e->cell(0) };
            Cell* c2 { e->cell(1) };

            // We suppose h1 > h2
            if (c1->ice_shift < c2->ice_shift)
            {
                Cell* c_tmp { c1 };

                c1 = c2;
                c2 = c_tmp;
            }

            // Calculate delta volume.

            if (c1->ice_shift > 0.0)
            {
                mid_area = c1->ice_chunk / c1->ice_shift;
            }
            else
            {
                mid_area = c1->area;
            }

            delta_v = mid_area * min(c1->ice_shift - c2->ice_shift,
                                     alfa * max_h);

            // Redistribute volume.
            c1->loc_ice_chunk -= beta * delta_v;
            c2->loc_ice_chunk += beta * delta_v;
        }

        // Put local ice chunks back.
        for (auto c : mesh.cells)
        {
            c->ice_chunk  = c->loc_ice_chunk;
        }

        // Define ice shifts again.
        define_ice_shifts(mesh);
    }
}

/// \brief Move nodes.
///
/// Move nodes.
///
/// \param[in,out] mesh Mesh.
void
Remesher::move_nodes(Mesh& mesh)
{
    // Define shifts.
    for (auto n : mesh.nodes)
    {
        geom::Vector::mul(n->ice_dir, n->ice_shift, n->shift);
    }

    // Update rest and actual ice volumes.
    for (auto c : mesh.cells)
    {
        const geom::Vector& p1 { c->node(0)->point };
        const geom::Vector& p2 { c->node(1)->point };
        const geom::Vector& p3 { c->node(2)->point };
        geom::Vector np1, np2, np3;

        geom::Vector::add(p1, c->node(0)->shift, np1);
        geom::Vector::add(p2, c->node(1)->shift, np2);
        geom::Vector::add(p3, c->node(2)->shift, np3);

        double v { geom::displaced_triangle_volume(p1, p2, p3,
                                                   np1, np2, np3) };

        c->rest_ice -= v;

        if (c->rest_ice < 0.0)
        {
            c->rest_ice = 0.0;
        }
    }

    // Move nodes.
    for (auto n : mesh.nodes)
    {
        geom::Vector::add(n->point, n->shift, n->point);
    }
}

/// \brief Calculate laplacian for null-space smoothing.
///
/// Calculate laplacian.
///
/// \param[in]  node Node.
/// \param[out] dv   Result.
void
Remesher::calc_laplacian(Node* node,
                         geom::Vector& dv)
{
    double weights { 0.0 };

    dv.zero();

    for (auto c : node->cells())
    {
        double weight { 0.0 };
        geom::Vector to_center;

        weight = c->area / c->saved_area;
        geom::Vector::sub(c->center, node->point, to_center);
        to_center.mul(weight);
        dv.add(to_center);
        weights += weight;
    }

    dv.div(weights);
}

/// \brief Null-space smoothing.
///
/// Smoothing in null-space.
///
/// sources:
/// 1. Jiao X.
///    Volume and feature preservation in surface mesh optimization.
/// 2. Jiao X.
///    Face offsetting: A unified approach for explicit moving interfaces.
/// 
/// \param[in,out] mesh Mesh.
/// \param[in]     opts Options.
void
Remesher::null_space_smoothing(Mesh& mesh,
                               const RemeshOptions& opts)
{
    int steps { opts.get_nss_steps() };

    if (steps == 0)
    {
        return;
    }

    double epsilon { opts.get_nss_epsilon() };
    double st { opts.get_nss_st() };

    for (int stepi = 0; stepi < steps; ++stepi)
    {
        // Save cells area.
        for (auto c : mesh.cells)
        {
            c->calc_area();
            c->saved_area = c->area;
        }

        // Loop for all nodes.
        for (auto node : mesh.nodes)
        {
            node->shift.zero();

            if (!node->is_inner())
            {
                // Process only inner nodes.
                continue;
            }

            // Create matrix of normals.
            vector<vector<double>> m;
            for (auto c : node->cells())
            {
                m.push_back(vector<double> { c->normal.x, c->normal.y, c->normal.z });
            }

            // Transpose matrix.
            vector<vector<double>> tm;
            mth::transpose(m, tm);

            // Create matrix of areas.
            vector<vector<double>> w(node->cells_count(), vector<double>(node->cells_count(), 0.0));
            for (size_t i = 0; i < node->cells_count(); ++i)
            {
                w[i][i] = node->cell(i)->area;
            }

            // Perform multiplication tm * w * m.
            vector<vector<double>> tm_w, a;
            mth::dot(tm, w, tm_w);
            mth::dot(tm_w, m, a);

            // Calculate eigenvalues and eigenvectords.
            vector<double> eigenvalues(3, 0.0);
            vector<vector<double>> eigenvectors(3, vector<double>(3, 0.0));
            mth::calc_eigenvalues_and_eigenvectors(a, eigenvalues, eigenvectors);

            // Process only cases when node is in smooth region.
            // One big eigenvalue.
            if (eigenvalues[1] > epsilon * eigenvalues[0])
            {
                continue;
            }

            // Erase 0-th eigenvalue and 0-th eigenvector.
            eigenvalues.erase(eigenvalues.begin());
            eigenvectors.erase(eigenvectors.begin());

            // Transpose rest eigenvectors.
            vector<vector<double>> transposed_eigenvectors;
            mth::transpose(eigenvectors, transposed_eigenvectors);

            // Multiplicate eigenvectors and transposed eigenvectors.
            vector<vector<double>> ttt;
            mth::dot(transposed_eigenvectors, eigenvectors, ttt);

            // Calculate laplacian.
            geom::Vector dv;
            calc_laplacian(node, dv);

            // Copy laplacian to vector.
            vector<double> dv_vector { dv.x, dv.y, dv.z };
            vector<double> tt;
            mth::dot(ttt, dv_vector, tt);

            // Copy result to direction.
            node->shift.set(tt[0], tt[1], tt[2]);
            node->shift.mul(st);
        }

        // Apply shifts.
        for (auto node : mesh.nodes)
        {
            node->point.add(node->shift);
        }

        // Recalculate geometry.
        mesh.update_cells_geometry();

        // Correct rest ice by areas.
        for (auto c : mesh.cells)
        {
            if (c->saved_area > 0.0)
            {
                double k { c->area / c->saved_area };

                c->rest_ice *= k;
            }
        }
    }
}

/// \brief Remesh one step with Tong method.
///
/// One step of Tong remeshing.
///
/// \param[in,out] mesh  Mesh.
/// \param[in]     opts Options.
/// \param[in]     stepi Step number (0 .. steps-1).
/// \param[in]     steps Steps count.
void
Remesher::remesh_tong_step(Mesh& mesh,
                           const RemeshOptions& opts,
                           int stepi,
                           int steps)
{
    // Calculate chunks.
    calc_ice_chunks(mesh, steps - stepi);

    // Init nodes and cells ice directions.
    init_ice_dirs(mesh);

    // Smooth normals.
    normals_smoothing(mesh, opts);

    // Define ice shifts.
    define_ice_shifts(mesh);

    // Smoothing heights.
    heights_smoothing(mesh, opts);

    // Move nodes.
    move_nodes(mesh);

    // Null-space smoothing.
    null_space_smoothing(mesh, opts);

    // Update geometry in the end.
    mesh.update_geometry();
}

/// \brief Remesh with Tong method.
///
/// Tong remeshing.
///
/// \param[in,out] mesh Mesh.
/// \param[in]     opts Options.
void
Remesher::remesh_tong(Mesh& mesh,
                      const RemeshOptions& opts)
{
    // Do not work with small amount of ice.
    zero_ice_below_threshold(mesh, opts.get_hi_as_zero_threshold());

    int steps = remeshing_nsteps(mesh, opts);

    // Preparations before remeshing.
    init_target_rest_ice(mesh);

    for (int stepi = 0; stepi < steps; ++stepi)
    {
        remesh_tong_step(mesh, opts, stepi, steps);
    }

    // In any case in the end we zero all ice.
    zero_ice(mesh);
}

//
// Main remesh method.
//

/// \brief Remesh.
///
/// Remesh with given method.
///
/// \param[in,out] mesh Mesh.
/// \param[in]     opts Options.
void
Remesher::remesh(Mesh& mesh,
                 const RemeshOptions& opts)
{
    switch (opts.get_method())
    {
        case RemeshMethod::Prisms:
            remesh_prisms(mesh, opts);
            break;

        case RemeshMethod::Tong:
            remesh_tong(mesh, opts);
            break;

        default:
            DEBUG_ERROR("unexpected remesh method");
    }
}

/// @}

}

}
