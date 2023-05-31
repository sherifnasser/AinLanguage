#include <iostream>
#include <memory>
#include <catch2/catch.hpp>
#include "LexerLine.hpp"
#include "LiteralToken.hpp"
#include "StringIsNotClosedException.hpp"

SCENARIO("Test LexerLine lexes a line", "[LexerLineTest.cpp]") {
    GIVEN("a line"){

        WHEN("the lines has string literal"){
            std::wstring line=L"\"string literal with \\\"DOULBE QOUTES\\\"\"";
            std::shared_ptr<LexerLine>lexerLine=std::make_shared<LexerLine>(line,1);

            THEN("Add LiteralToken::STRING to tokens"){
                lexerLine->tokenize();
                auto tokens=lexerLine->getTokens();
                REQUIRE(tokens->size()==1);
                std::shared_ptr<LexerToken> token=tokens->at(0);
                auto literalToken=std::dynamic_pointer_cast<LiteralToken>(token);
                REQUIRE(literalToken!=nullptr);
                REQUIRE(literalToken->getLiteralType()==LiteralToken::STRING);
                REQUIRE(literalToken->getTokenType()==LexerToken::LITERAL_TOKEN);
                REQUIRE(literalToken->getVal()==line);
            };
        };

        WHEN("String is not closed"){

            std::wstring literal=L"\"string literal with \\\"DOULBE QOUTES\\\"";
            auto lexerLine=LexerLine(literal,1);
            
            THEN("Throw StringIsNotClosedException (There're letters after first \")"){
                auto matcher=Catch::Matchers::Predicate<StringIsNotClosedException>(
                    [&](StringIsNotClosedException e){
                        std::string what=e.what();
                        return what.find("\"string literal with \\\"DOULBE QOUTES\\\"") != std::string::npos;
                    }
                );
                REQUIRE_THROWS_MATCHES(
                    lexerLine.tokenize(),
                    StringIsNotClosedException,
                    matcher
                );
            };

            THEN("Throw StringIsNotClosedException (There're no letters after first \")"){
                literal=L"\"";
                REQUIRE_THROWS_AS(
                    lexerLine.tokenize(),
                    StringIsNotClosedException
                );
            };
        };
    }
}