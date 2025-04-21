/// \file
/// \brief Unit-tests for utils_string.
///
/// Unit-tests for utils_string.

#include <catch2/catch_test_macros.hpp>
#include "caesar.h"

using namespace caesar;

TEST_CASE("string : find_word function", "[utils]")
{
    SECTION("find all words")
    {
        string s { "  one  two   three    four  " };
        size_t p { 0 };
        size_t len { 0 };
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

TEST_CASE("string : split_into_words function", "[utils]")
{
    SECTION("comma separator")
    {
        const string comma { "," };
        const string s { "one,two,three" };
        vector<string> ss;

        utils::split_into_words(s, comma, ss);

        CHECK(ss.size() == 3);
        CHECK(ss[0] == "one");
        CHECK(ss[1] == "two");
        CHECK(ss[2] == "three");
    }

    SECTION("comma separator, ignore spaces")
    {
        // issue #46 - we have to ignore spaces
        const string comma { ", " };
        const string s { "one,two ,three, four , five" };
        vector<string> ss;

        utils::split_into_words(s, comma, ss);

        CHECK(ss.size() == 5);
        CHECK(ss[0] == "one");
        CHECK(ss[1] == "two");
        CHECK(ss[2] == "three");
        CHECK(ss[3] == "four");
        CHECK(ss[4] == "five");
    }
}

TEST_CASE("string : find_substr_in_double_quotes function", "[utils]")
{
    SECTION("positive and neagtive cases")
    {
        string s { "  \"test\"  " };
        size_t p { 0 };
        size_t len { 0 };
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

    SECTION("find empty substring")
    {
        string s { "\"\"" };
        size_t p { 0 };
        size_t len { 0 };
        bool r { false };

        r = utils::find_substr_in_double_quotes(s, 0, p, len);
        CHECK(r);
        CHECK(p == 1);
        CHECK(len == 0);
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
        size_t lo { 0 }, hi { 0 };
        bool r { false };

        r = utils::find_interval_int_bounds_in_str(s, lo, hi);
        CHECK(r);
        CHECK(lo == 10);
        CHECK(hi == 30);
    }
}

TEST_CASE("string : convert", "[utils]")
{
    SECTION("convert to double")
    {
        string spu { "1.0e-320" }, snu { "-1.0e-320" };
        string spo { "1.0e+320" }, sno { "-1.0e+320" };
        double dpu { utils::convert_to_double(spu) };
        double dnu { utils::convert_to_double(snu) };
        double dpo { utils::convert_to_double(spo) };
        double dno { utils::convert_to_double(sno) };

        CHECK(mth::is_zero(dpu));
        CHECK(mth::is_zero(dnu));
        CHECK(isinf(dpo));
        CHECK(isinf(dno));
    }
}
