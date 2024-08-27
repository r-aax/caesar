/// \file
/// \brief Tests for mapper.
///
/// Mapper tests.

#include <catch2/catch_test_macros.hpp>
#include "utils/utils_mapper.h"

/// \brief Test enum from 0.
///
/// Test enum from 0.
enum class TestEnumFrom0
{
    /// \brief First element.
    First = 0,

    /// \brief Test enum zero.
    Zero = First,

    /// \brief Test enum two.
    One,

    /// \brief Test enum three.
    Two,

    /// \brief Last element.
    Last = Two
};

/// \brief Test enum from 10.
///
/// Test enum from 10.
enum class TestEnumFrom10
{
    /// \brief First element.
    First = 10,

    /// \brief Test enum ten.
    Ten = First,

    /// \brief Test enum eleven.
    Eleven,

    /// \brief Test enum twelve.
    Twelve,

    /// \brief Last element.
    Last = Twelve
};

TEST_CASE("Mapper : mapper betweeen names and enums", "[utils]")
{
    SECTION("test enum from 0")
    {
        utils::Mapper<TestEnumFrom0> m("test_enum_from_0", vector<string> { "Zero", "One", "Two" });

        CHECK(m.get_name(TestEnumFrom0::Zero) == "Zero");
        CHECK(m.get_name(TestEnumFrom0::One) == "One");
        CHECK(m.get_name(TestEnumFrom0::Two) == "Two");
        CHECK(m.get_enum("Zero") == TestEnumFrom0::Zero);
        CHECK(m.get_enum("One") == TestEnumFrom0::One);
        CHECK(m.get_enum("Two") == TestEnumFrom0::Two);
    }

    SECTION("test enum from 10")
    {
        utils::Mapper<TestEnumFrom10> m("test_enum_from_10", vector<string> { "Ten", "Eleven", "Twelve" });

        CHECK(m.get_name(TestEnumFrom10::Ten) == "Ten");
        CHECK(m.get_name(TestEnumFrom10::Eleven) == "Eleven");
        CHECK(m.get_name(TestEnumFrom10::Twelve) == "Twelve");
        CHECK(m.get_enum("Ten") == TestEnumFrom10::Ten);
        CHECK(m.get_enum("Eleven") == TestEnumFrom10::Eleven);
        CHECK(m.get_enum("Twelve") == TestEnumFrom10::Twelve);
    }
} 
