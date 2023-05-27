
#define CATCH_CONFIG_MAIN
#include <iostream>
#include <catch2/catch.hpp>
#include <symboltoken.hpp>


SCENARIO("Example test", "[test.cpp]") {
    GIVEN("SOME"){
        WHEN("NOTHING"){
            THEN("Plus is +"){
                REQUIRE(symboltoken::PLUS.getval() == L"+");
            }
            THEN("Minus is -"){
                REQUIRE(symboltoken::MINUS.getval() == L"-");
            }
        }
    }
    
}

TEST_CASE("Example test2", "[test.cpp]") {
    REQUIRE(2 + 2 == 4);
}