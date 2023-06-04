#include <iostream>
#include <memory>
#include <catch2/catch.hpp>
#include "string_helper.hpp"
#include "LexerLine.hpp"
#include "LiteralToken.hpp"
#include "SymbolToken.hpp"
#include "NumberToken.hpp"
#include "StringIsNotClosedException.hpp"
#include "IllegalUnderscoreException.hpp"
#include "UnsupportedTokenException.hpp"
#include "OutOfRangeException.hpp"

SCENARIO("Test LexerLine lexes a line", "[LexerLineTest.cpp]") {
    GIVEN("a line"){

        WHEN("the line has string literal"){
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
                        return e.whatWstr().find(literal) != std::string::npos;
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
                    REQUIRE(token->getTokenType()==LexerToken::SYMBOL_TOKEN);
                    REQUIRE(token->operator==(expectedTokens[i]));
                    i++;
                }
            }
        };

        WHEN("line has number literals"){

            THEN("Tokenize legals"){
                NumberToken legals[]={
                    NumberToken(NumberToken::INT,L"3"),
                    NumberToken(NumberToken::INT,L"30"),
                    NumberToken(NumberToken::LONG,L"4545544L"),
                    NumberToken(NumberToken::LONG,L"30l"),
                    NumberToken(NumberToken::DOUBLE,L"3.0"),
                    NumberToken(NumberToken::DOUBLE,L"3e0"),
                    NumberToken(NumberToken::DOUBLE,L"3e2"),
                    NumberToken(NumberToken::DOUBLE,L"3E2"),
                    NumberToken(NumberToken::DOUBLE,L"3.0e2"),
                    NumberToken(NumberToken::DOUBLE,L"3.0e-2"),
                    NumberToken(NumberToken::DOUBLE,L"3.0e-2_0"),
                    NumberToken(NumberToken::FLOAT,L"3.00f"),
                    NumberToken(NumberToken::FLOAT,L"3.00F"),
                    NumberToken(NumberToken::INT,L"3_3_3__0"),
                    NumberToken(NumberToken::INT,L"32_23_23_2_20"),
                    NumberToken(NumberToken::DOUBLE,L"12.54e1"),
                    NumberToken(NumberToken::FLOAT,L"12.54e1f"),
                    NumberToken(NumberToken::FLOAT,L"12.54e-1f"),
                    NumberToken(NumberToken::FLOAT,L"1_2.5_4e1_2f"),
                    NumberToken(NumberToken::UNSIGNED_INT,L"12U"),
                    NumberToken(NumberToken::UNSIGNED_INT,L"12u"),
                    NumberToken(NumberToken::UNSIGNED_LONG,L"12ul"),
                    NumberToken(NumberToken::UNSIGNED_LONG,L"12UL"),
                    NumberToken(NumberToken::UNSIGNED_LONG,L"12uL"),
                    NumberToken(NumberToken::UNSIGNED_LONG,L"12Ul"),
                };

                int i=0;
                for(auto &legal:legals){
                    auto val=legal.getVal();
                    auto lexerLine=LexerLine(val,i);
                    lexerLine.tokenize();
                    auto numToken=std::dynamic_pointer_cast<NumberToken>(
                        lexerLine.getTokens()->at(0)
                    );
                    auto expected=val;
                    removeUnderscores(&expected);
                    switch(legal.getNumberType()){
                        case NumberToken::LONG:
                        expected=std::to_wstring(std::stoll(expected));
                        break;
                        case NumberToken::UNSIGNED_INT:
                        expected=std::to_wstring(std::stoull(expected));
                        break;
                        case NumberToken::UNSIGNED_LONG:
                        expected=std::to_wstring(std::stoull(expected));
                        break;
                        case NumberToken::DOUBLE:
                        expected=std::to_wstring(std::stold(expected));
                        break;
                        case NumberToken::FLOAT:
                        expected=std::to_wstring(std::stof(expected));
                        break;
                    }
                    REQUIRE(lexerLine.getTokens()->size()==1);
                    REQUIRE(expected==numToken->getVal());
                    REQUIRE(legal.getNumberType()==numToken->getNumberType());
                    REQUIRE(legal.getLiteralType()==numToken->getLiteralType());
                    REQUIRE(legal.getTokenType()==numToken->getTokenType());
                    i++;
                }
            };

            THEN("Tokenize legals with different number system"){
                auto legalNumSys=std::map<std::wstring,std::wstring>{
                    {L"12",L"12"},
                    {L"0b10100",L"20"},
                    {L"0B10_101",L"21"},
                    {L"0o12",L"10"},
                    {L"0O12__34",L"668"},
                    {L"0x1_2",L"18"},
                    {L"0XA_bFF_4",L"704500"},
                };
                int i=0;
                for(auto &legal:legalNumSys){
                    auto val1=legal.first;
                    auto val2=legal.second;
                    auto lexerLine=LexerLine(val1,i);
                    lexerLine.tokenize();
                    auto numToken=std::dynamic_pointer_cast<NumberToken>(
                        lexerLine.getTokens()->at(0)
                    );
                    REQUIRE(lexerLine.getTokens()->size()==1);
                    REQUIRE(val2==numToken->getVal());
                    REQUIRE(numToken->getNumberType()==NumberToken::INT);
                    REQUIRE(numToken->getLiteralType()==LiteralToken::NUMBER);
                    REQUIRE(numToken->getTokenType()==LexerToken::LITERAL_TOKEN);
                    i++;
                }
            };

            THEN("Throw IllegalUnderscoreException when there is illegal underscore"){
                std::wstring illegalUnderscore[]={
                    L"12_",
                    L"3_.0",
                    L"3._0",
                    L"3.0_",
                    L"4_e2",
                    L"4e_2",
                    L"4e2_",
                    L"15.64_e5",
                    L"15321__.166_f",
                };

                int i=0;
                for(auto &illegal:illegalUnderscore){
                    auto lexerLine=LexerLine(illegal,i);
                    auto matcher=Catch::Matchers::Predicate<IllegalUnderscoreException>(
                        [&](IllegalUnderscoreException e){
                            auto npos=std::wstring::npos;
                            auto what=e.whatWstr();
                            return
                                what.find(std::to_wstring(i))!=npos
                                &&
                                what.find(
                                    illegal.substr(0,illegal.find(L'_')+1)
                                )!=npos
                            ;
                        }
                    );
                    REQUIRE_THROWS_MATCHES(
                        lexerLine.tokenize(),
                        IllegalUnderscoreException,
                        matcher
                    );
                    i++;
                }
            };

            THEN("Throw UnsupportedTokenException when cannot construct tokens"){
                std::wstring unsupported[]={
                    L"3.",
                    L"3..0",
                    L"3.0e",

                    /**
                     * May be tested in parser
                    */

                    /*L"4ac",
                    L"0xa165.166",
                    L"0Ba165.166",
                    L"0oa165.166",
                    L"0b1215",
                    L"0o1289",
                    L"0x121s",*/
                    
                };
                int i=0;
                for(auto &illegal:unsupported){
                    auto lexerLine=LexerLine(illegal,i);
                    REQUIRE_THROWS_AS(
                        lexerLine.tokenize(),
                        UnsupportedTokenException
                    );
                    i++;
                }
            };

            THEN("Throw OutOfRangeException when exceeds the maximum limits of data types"){
                std::wstring outOfRange[]={
                    L"3.5e38f",   // > FLOAT_MAX
                    L"1.16e-38f", // < FLOAT_MIN
                    L"1.19973e+4932", // > DOUBLE_MAX
                    L"3.3521e-4932", // < DOUBLE_MIN
                    L"9223372036854775808" // > LONG_MAX
                    L"18446744073709551616" // > ULONG_MAX
                };
                int i=0;
                for(auto &illegal:outOfRange){
                    auto lexerLine=LexerLine(illegal,i);
                    auto matcher=Catch::Matchers::Predicate<OutOfRangeException>(
                        [&](OutOfRangeException e){
                            auto npos=std::wstring::npos;
                            auto what=e.whatWstr();
                            return what.find(std::to_wstring(i))!=npos && what.find(illegal)!=npos;
                        }
                    );
                    REQUIRE_THROWS_MATCHES(
                        lexerLine.tokenize(),
                        OutOfRangeException,
                        matcher
                    );
                    i++;
                }
            };
            
        };
    }
}