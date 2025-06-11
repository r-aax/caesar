/// \file
/// \brief Tests for mapper.
///
/// Mapper tests.

#include <catch2/catch_test_macros.hpp>
#include "caesar.h"

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
        caesar::utils::Mapper<TestEnumFrom0> m("test_enum_from_0",
                                               vector<string> { "Zero", "One", "Two" });

        CHECK(m.name(TestEnumFrom0::Zero) == "Zero");
        CHECK(m.name(TestEnumFrom0::One)  == "One");
        CHECK(m.name(TestEnumFrom0::Two)  == "Two");
        CHECK(m.repr(TestEnumFrom0::Zero) == "Zero (0)");
        CHECK(m.repr(TestEnumFrom0::One)  == "One (1)");
        CHECK(m.repr(TestEnumFrom0::Two)  == "Two (2)");
        CHECK(m.num("Zero") == TestEnumFrom0::Zero);
        CHECK(m.num("One")  == TestEnumFrom0::One);
        CHECK(m.num("Two")  == TestEnumFrom0::Two);
    }

    SECTION("test enum from 10")
    {
        caesar::utils::Mapper<TestEnumFrom10> m("test_enum_from_10",
                                                vector<string> { "Ten", "Eleven", "Twelve" });

        CHECK(m.name(TestEnumFrom10::Ten)    == "Ten");
        CHECK(m.name(TestEnumFrom10::Eleven) == "Eleven");
        CHECK(m.name(TestEnumFrom10::Twelve) == "Twelve");
        CHECK(m.repr(TestEnumFrom10::Ten)    == "Ten (10)");
        CHECK(m.repr(TestEnumFrom10::Eleven) == "Eleven (11)");
        CHECK(m.repr(TestEnumFrom10::Twelve) == "Twelve (12)");
        CHECK(m.num("Ten")    == TestEnumFrom10::Ten);
        CHECK(m.num("Eleven") == TestEnumFrom10::Eleven);
        CHECK(m.num("Twelve") == TestEnumFrom10::Twelve);
    }
}
