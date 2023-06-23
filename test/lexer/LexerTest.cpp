
#include "LexerToken.hpp"
#define CATCH_CONFIG_MAIN
#include <iostream>
#include <memory>
#include <catch2/catch.hpp>
#include "Lexer.hpp"
#include "LinkedList.hpp"

class FakeAinFile: public IAinFile{
    private:
        void readAinFile(std::string& path) override{}

        std::vector<std::wstring> getLines() override{
            return {
                L"line0",
                L"\t",
                L"\tLine1",
                L"\t   ",
                L"   \v",
                L"\v",
                L"\t\tLine2",
            };
        }
};

SCENARIO("Test Lexer","[LexerTest.cpp]"){
    WHEN("some lines are empty"){
        THEN("Ignore lexing these lines"){
            auto file=std::make_shared<FakeAinFile>();
            Lexer lexer(file);
            REQUIRE(lexer.getTokens()->tail->val->getTokenType()==LexerToken::EOF_TOKEN);
        }
    }
}