/// \file
/// \brief Unit-tests for utils_filesystem.
///
/// Unit-tests for utils_filesystem.

#include <catch2/catch_test_macros.hpp>
#include "caesar.h"

using namespace caesar;

TEST_CASE("filesystem : filename functions", "[utils]")
{
    SECTION("filename_stem")
    {
        CHECK(utils::filename_stem("test") == "test");
        CHECK(utils::filename_stem("test.txt") == "test");
        CHECK(utils::filename_stem("path/test") == "test");
        CHECK(utils::filename_stem("path/test.txt") == "test");
        CHECK(utils::filename_stem("path/test.txt.txt") == "test.txt");
    }
}
