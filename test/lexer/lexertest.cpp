
#define CATCH_CONFIG_MAIN
#include <iostream>
#include <catch2/catch.hpp>
#include <symboltoken.hpp>


SCENARIO("Example test", "[lexertest.cpp]") {
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