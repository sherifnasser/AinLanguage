#include <catch2/catch.hpp>
#include "FunParamater.hpp"
#include "Type.hpp"

TEST_CASE("FunParamater tests", "[FunParamaterTest.cpp]") {
    // Create some shared pointers to test data
    auto paramName = std::make_shared<std::wstring>(L"myParam");
    auto intType = Type::INT;
    auto doubleType=Type::DOUBLE;

    SECTION("constructor sets properties correctly") {
        // Create a new FunParamater object
        FunParamater myParam(paramName, intType);

        // Check that the object's properties were set correctly
        REQUIRE(myParam.name == paramName);
        REQUIRE(myParam.type == intType);
    }

    SECTION("equality operator returns true for equal objects") {
        // Create two FunParamater objects with identical properties
        FunParamater myParam1(paramName, intType);
        FunParamater myParam2(paramName, intType);

        // Check that the equality operator returns true
        REQUIRE(myParam1 == myParam2);
    }

    SECTION("equality operator returns false for objects with different names") {
        // Create two FunParamater objects with different names
        SharedWString paramName1 = std::make_shared<std::wstring>(L"myParam1");
        SharedWString paramName2 = std::make_shared<std::wstring>(L"myParam2");
        FunParamater myParam1(paramName1, intType);
        FunParamater myParam2(paramName2, intType);

        // Check that the equality operator returns false
        REQUIRE_FALSE(myParam1 == myParam2);
    }

    SECTION("equality operator returns false for objects with different types") {
        // Create two FunParamater objects with different types
        FunParamater myParam1(paramName, intType);
        FunParamater myParam2(paramName, doubleType);

        // Check that the equality operator returns false
        REQUIRE_FALSE(myParam1 == myParam2);
    }

    SECTION("inequality operator returns true for unequal objects") {
        // Create two FunParamater objects with different names and types
        SharedWString paramName1 = std::make_shared<std::wstring>(L"myParam1");
        SharedWString paramName2 = std::make_shared<std::wstring>(L"myParam2");
        FunParamater myParam1(paramName1, intType);
        FunParamater myParam2(paramName2, doubleType);

        // Check that the inequality operator returns true
        REQUIRE(myParam1 != myParam2);
    }

    SECTION("inequality operator returns false for equal objects") {
        // Create two FunParamater objects with identical properties
        FunParamater myParam1(paramName, intType);
        FunParamater myParam2(paramName, intType);

        // Check that the inequality operator returns false
        REQUIRE_FALSE(myParam1 != myParam2);
    }
}