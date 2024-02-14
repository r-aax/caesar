/// \file
/// \brief Unit-tests for utils_string.
///
/// Unit-tests for utils_string.

#include "utils/utils.h"
#include <catch2/catch.hpp>

TEST_CASE("string : find_word function", "[utils]")
{
    SECTION("find all words")
    {
        string s { "  one  two   three    four  " };
        int p { 0 }, len { 0 };
        bool r { false };

        r = utils::find_word(s, 0, p, len);
        CHECK(r);
        CHECK(p == 2);
        CHECK(len == 3);

        r = utils::find_word(s, p + len + 1, p, len);
        CHECK(r);
        CHECK(p == 7);
        CHECK(len == 3);

        r = utils::find_word(s, p + len + 1, p, len);
        CHECK(r);
        CHECK(p == 13);
        CHECK(len == 5);

        r = utils::find_word(s, p + len + 1, p, len);
        CHECK(r);
        CHECK(p == 22);
        CHECK(len == 4);

        r = utils::find_word(s, p + len + 1, p, len);
        CHECK_FALSE(r);
    }
}

TEST_CASE("string : find_substr_in_double_quotes function", "[utils]")
{
    SECTION("positive and neagtive cases")
    {
        string s { "  \"test\"  " };
        int p { 0 }, len { 0 };
        bool r { false };

        r = utils::find_substr_in_double_quotes(s, 0, p, len);
        CHECK(r);
        CHECK(p == 3);
        CHECK(len == 4);

        r = utils::find_substr_in_double_quotes(s, 4, p, len);
        CHECK_FALSE(r);

        r = utils::find_substr_in_double_quotes(s, 100, p, len);
        CHECK_FALSE(r);
    }
}

TEST_CASE("string : get_int_from_str_after_eq_sign function", "[utils]")
{
    SECTION("positive and neagtive cases")
    {
        string s { "NAME=25" };
        int v { 0 };

        v = utils::get_int_from_str_after_eq_sign(s);
        CHECK(v == 25);
    }
}

TEST_CASE("string : find_interval_int_bounds_in_str", "[utils]")
{
    SECTION("positive and neagtive cases")
    {
        string s { "bounds = [10-30]" };
        int lo { 0 }, hi { 0 };
        bool r { false };

        r = utils::find_interval_int_bounds_in_str(s, lo, hi);
        CHECK(r);
        CHECK(lo == 10);
        CHECK(hi == 30);
    }
}
