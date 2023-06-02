#include <iostream>
#include <memory>
#include <catch2/catch.hpp>
#include "LexerLine.hpp"
#include "LiteralToken.hpp"
#include "SymbolToken.hpp"
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

        WHEN("Line is a single-line comment"){
            std::wstring line=L"// This is a single-line comment";
            auto expectedToken=LexerToken(LexerToken::COMMENT_TOKEN,line);
            std::shared_ptr<LexerLine>lexerLine=std::make_shared<LexerLine>(line,1);
            THEN("Add comment token to tokens"){
                lexerLine->tokenize();
                auto tokens=lexerLine->getTokens();
                REQUIRE(tokens->size()==1);
                auto commentToken=tokens->at(0);
                REQUIRE(commentToken->operator==(expectedToken));
            }
        };

        WHEN("Line has ain puncts (has arabic puncts)"){
            std::wstring line=L"(){}[]<>:=+-*/%!^&|\\.>=<===!=&&||+=-=*=/=%=^=،؛؟";
            std::vector<SymbolToken> expectedTokens={
                SymbolToken::LEFT_PARENTHESIS,SymbolToken::RIGHT_PARENTHESIS,
                SymbolToken::LEFT_CURLY_BRACES,SymbolToken::RIGHT_CURLY_BRACES,
                SymbolToken::LEFT_SQUARE_BRACKET,SymbolToken::RIGHT_SQUARE_BRACKET,
                SymbolToken::LEFT_ANGLE_BRACKET,SymbolToken::RIGHT_ANGLE_BRACKET,
                SymbolToken::COLON,SymbolToken::EQUAL,
                SymbolToken::PLUS,SymbolToken::MINUS,SymbolToken::STAR,SymbolToken::SLASH,SymbolToken::MODULO,
                SymbolToken::EXCLAMATION_MARK,
                SymbolToken::POWER,SymbolToken::AMPERSAND,SymbolToken::BAR,SymbolToken::BACK_SLASH,
                SymbolToken::DOT,
                SymbolToken::GREATER_EQUAL,SymbolToken::LESS_EQUAL,SymbolToken::EQUAL_EQUAL,SymbolToken::NOT_EQUAL,
                SymbolToken::LOGICAL_AND,SymbolToken::LOGICAL_OR,
                SymbolToken::PLUS_EQUAL,SymbolToken::MINUS_EQUAL,
                SymbolToken::STAR_EQUAL,SymbolToken::SLASH_EQUAL,
                SymbolToken::MODULO_EQUAL,SymbolToken::POWER_EQUAL,
                SymbolToken::COMMA,SymbolToken::SEMICOLON,SymbolToken::QUESTION_MARK,
            };
            std::shared_ptr<LexerLine>lexerLine=std::make_shared<LexerLine>(line,1);
            THEN("Gives correct tokens"){
                lexerLine->tokenize();
                auto tokens=lexerLine->getTokens();
                REQUIRE(tokens->size()==expectedTokens.size());
                int i=0;
                for(auto &token:*tokens){
                    REQUIRE_NOTHROW(std::dynamic_pointer_cast<SymbolToken>(token));
                    REQUIRE(token->operator==(expectedTokens[i]));
                    i++;
                }
            }
        };
    }
}