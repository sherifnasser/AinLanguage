
#include <iostream>
#include <catch2/catch.hpp>
#include <symboltoken.hpp>



TEST_CASE("Example test3", "[test2.cpp]") {
    REQUIRE(symboltoken::PLUS.getval() == L"+");
}

TEST_CASE("Example test4", "[test2.cpp]") {
    REQUIRE(2 + 2 == 4);
}