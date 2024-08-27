/// \file
/// \brief Tests for vectors.
///
/// Tests for vectors.

#include <catch2/catch_test_macros.hpp>
#include "caesar.h"

using namespace caesar;

TEST_CASE("Vector : 3D vector", "[geom]")
{
    SECTION("distance")
    {
        geom::Vector a(1.0, 1.0, 1.0), b(2.0, 2.0, 2.0), c(1.0, 1.0, -1.0);

        CHECK(mth::is_near(a.dist_to(b), sqrt(3.0)));
        CHECK(mth::is_near(a.dist_to(c), 2.0));
    }

    SECTION("scalar product")
    {
        geom::Vector a(1.0, 0.0, 0.0), b(1.0, 1.0, 0.0);

        CHECK(mth::is_near(a * b, 1.0));
        CHECK(mth::is_near(geom::Vector::angle_cos(a, b), 1.0 / sqrt(2.0)));
    }

    SECTION("co- and counter-directed vectors")
    {
        geom::Vector a(1.0, 1.0, 1.0), b(2.0, 2.0, 2.0), c(-3.0, -3.0, -3.0);

        CHECK(geom::Vector::is_co_directed(a, b));
        CHECK(geom::Vector::is_counter_directed(a, c));
    }

    SECTION("projection_value on vector")
    {
        geom::Vector base(1.0, 0.0, 0.0), pos(1.0, 1.0, 0.0), neg(-1.0, 1.0, 0.0);

        double pos_p = pos.projection_value(base);
        double neg_p = neg.projection_value(base);

        CHECK(mth::is_near(pos_p, 1.0));
        CHECK(mth::is_near(neg_p, -1.0));
    }

    SECTION("calc_projection on vector")
    {
        geom::Vector base(1.0, 0.0, 0.0), pos(1.0, 1.0, 0.0), neg(-1.0, 1.0, 0.0);
        geom::Vector pos_projection, neg_projection;
        geom::Vector pos_projection_right(1.0, 0.0, 0.0), neg_projection_right(-1.0, 0.0, 0.0);

        pos.calc_projection(base, pos_projection);
        neg.calc_projection(base, neg_projection);

        CHECK(pos_projection.is_near(pos_projection_right));
        CHECK(neg_projection.is_near(neg_projection_right));
    }

    SECTION("orthogonal decomposition")
    {
        geom::Vector base(1.0, 0.0, 0.0);
        geom::Vector v(1.0, 1.0, 0.0);
        geom::Vector p, n, p_right(1.0, 0.0, 0.0), n_right(0.0, 1.0, 0.0);;

        v.orthogonal_decompose(base, p, n);

        CHECK(p.is_near(p_right));
        CHECK(n.is_near(n_right));
    }

    SECTION("calc_projection_on_plane function")
    {
        geom::Vector a(0.0, 0.0, 0.0), b(1.0, 0.0, 1.0), c(1.0, 0.0, -1.0);
        geom::Vector v(1.0, 1.0, 0.0);
        geom::Vector p, p_right(1.0, 0.0, 0.0);

        v.calc_projection_on_plane(a, b, c, p);

        CHECK(p.is_near(p_right));
    }

    SECTION("calc_height_dir function")
    {
        geom::Vector a(1.0, 1.0, 0.0), b(-1.0, 1.0, 0.0), r, r_right(0.0, 1.0, 0.0);

        geom::Vector::calc_height_dir(a, b, r);

        CHECK(r.is_near(r_right));
    }

    SECTION("triangle linear characterristics")
    {
        geom::Vector a(0.0, 0.0, 0.0), b(1.0, 0.0, 0.0), c(0.0, 1.0, 0.0);
        double min_side = geom::Vector::triangle_min_side_length(a, b, c);

        CHECK(mth::is_near(min_side, 1.0));
    }

    SECTION("triangle area")
    {
        geom::Vector a(0.0, 0.0, 0.0), b(1.0, 0.0, 0.0), c(0.0, 1.0, 0.0);
        double s = geom::Vector::triangle_area(a, b, c);

        CHECK(mth::is_near(s, 0.5));
    }

    SECTION("tetrahedron volume")
    {
        geom::Vector a(0.0, 0.0, 0.0), b(1.0, 0.0, 0.0), c(0.0, 1.0, 0.0), d(0.0, 0.0, 1.0);
        double v = geom::Vector::tetrahedron_volume(a, b, c, d);

        CHECK(mth::is_near(v, (1.0 / 6.0)));
    }

    SECTION("dislplaced triangle volume")
    {
        geom::Vector ao(0.0, 0.0, 0.0), bo(1.0, 0.0, 0.0), co(1.0, 1.0, 0.0),
                     an(0.0, 0.0, 1.0), bn(1.0, 0.0, 1.0), cn(1.0, 1.0, 1.0);
        double v = geom::Vector::displaced_triangle_volume(ao, bo, co, an, bn, cn);

        CHECK(mth::is_near(v, 0.5));
    }
}
