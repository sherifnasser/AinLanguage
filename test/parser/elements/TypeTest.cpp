#include <catch2/catch.hpp>
#include "Type.hpp"

TEST_CASE("Type tests", "[TypeTest.cpp]") {
    // Create some shared pointers to test data
    auto intTypeName=Type::INT->name;
    auto doubleTypeName=Type::DOUBLE->name;

    SECTION("constructor sets name property correctly") {
        // Create a new Type object
        Type intType(intTypeName);

        // Check that the object's name property was set correctly
        REQUIRE(intType.name == intTypeName);
    }

    SECTION("equality operator returns true for equal objects") {
        // Create two Type objects with identical names
        Type intType1(intTypeName);
        Type intType2(intTypeName);

        // Check that the equality operator returns true
        REQUIRE(intType1 == intType2);
    }

    SECTION("equality operator returns false for objects with different names") {
        // Create two Type objects with different names
        Type intType(intTypeName);
        Type doubleType(doubleTypeName);

        // Check that the equality operator returns false
        REQUIRE_FALSE(intType == doubleType);
    }

    SECTION("inequality operator returns true for unequal objects") {
        // Create two Type objects with different names
        Type intType(intTypeName);
        Type doubleType(doubleTypeName);

        // Check that the inequality operator returns true
        REQUIRE(intType != doubleType);
    }

    SECTION("inequality operator returns false for equal objects") {
        // Create two Type objects with identical names
        Type intType1(intTypeName);
        Type intType2(intTypeName);

        // Check that the inequality operator returns false
        REQUIRE_FALSE(intType1 != intType2);
    }
}