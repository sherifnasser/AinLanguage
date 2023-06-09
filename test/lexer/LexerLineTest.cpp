#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include <map>
#include <catch2/catch.hpp>
#include "string_helper.hpp"
#include "LexerLine.hpp"
#include "LiteralToken.hpp"
#include "SymbolToken.hpp"
#include "NumberToken.hpp"
#include "KeywordToken.hpp"
#include "MissingQouteException.hpp"
#include "InvalidLengthCharacterLiteralException.hpp"
#include "InvalidEscapeSequenceException.hpp"
#include "InvalidUniversalCharacterCodeException.hpp"
#include "IllegalUnderscoreException.hpp"
#include "UnsupportedTokenException.hpp"
#include "OutOfRangeException.hpp"
#include "InvalidNumberSystemDigitException.hpp"
#include "InvalidIdentifierNameException.hpp"
#include "ContainsKufrOrUnsupportedCharacterException.hpp"

struct IdentifierTestToken:public LexerToken{
    IdentifierTestToken(std::wstring val):
    LexerToken(LexerToken::IDENTIFIER_TOKEN,val){}
};

/**
 * @brief Given illegal tokens in @param illegals, when calling lexerLine.tokenize()
 * We expect to find each illegal token in exception message and the line number.
 * @tparam E type of the expected exception
*/

template<typename E>
void LexerLineTokensTestWithException(
    std::vector<std::wstring> illegals,
    std::function<std::wstring(std::wstring&)> illegalExpected=
    [](std::wstring &illegal){return illegal;}
){
    int i=0;
    for(auto &illegal:illegals){
        auto lexerLine=LexerLine(illegal,i);
        auto expectedInMsg=illegalExpected(illegal);
        auto matcher=Catch::Matchers::Predicate<E>(
            [&](E e){
                auto what=e.whatWstr();
                auto npos=std::wstring::npos;
                return what.find(std::to_wstring(i))!=npos && what.find(expectedInMsg)!=npos;
            }
        );
        REQUIRE_THROWS_MATCHES(lexerLine.tokenize(),E,matcher);
        i++;
    }
}

SCENARIO("Test LexerLine lexes a line", "[LexerLineTest.cpp]") {
    GIVEN("a line"){

        WHEN("Has kufr or unsupported character (in string or char literls)"){
            std::vector<std::wstring> illegals={
                L"\"\\ي0900\"",
                L"\'\\ي0900\'",
            };

            THEN("Throw ContainsKufrOrUnsupportedCharacterException"){
                LexerLineTokensTestWithException<ContainsKufrOrUnsupportedCharacterException>(illegals);
            };
        };

        WHEN("the line has string literal"){
            std::wstring line=L"\"string \\خ\\ف\\س\\ر\\ص\\ج\\\\ literal with\\\'\\\' \\\"QOUTES\\\" \\س and \\ي0041\\ي0042\"";
            // expected to replace unescaped characters with escaped versions, also unicode characters
            std::wstring expected=L"\"string \b\t\n\v\f\r\\ literal with\'\' \"QOUTES\" \n and \u0041\u0042\"";
            LexerLine lexerLine=LexerLine(line,1);

            THEN("Add LiteralToken::STRING to tokens"){
                lexerLine.tokenize();
                auto tokens=lexerLine.getTokens();
                for(auto &token:*tokens){
                    //std::wcout<<token->getVal()<<token->getTokenType()<<std::endl;
                }
                REQUIRE(tokens->size()==1);
                std::shared_ptr<LexerToken> token=tokens->at(0);
                auto literalToken=std::dynamic_pointer_cast<LiteralToken>(token);
                REQUIRE(literalToken!=nullptr);
                REQUIRE(literalToken->getLiteralType()==LiteralToken::STRING);
                REQUIRE(literalToken->getTokenType()==LexerToken::LITERAL_TOKEN);
                REQUIRE(literalToken->getVal()==expected);
            };
        };

        WHEN("the line has character literal"){
            std::vector<std::wstring> legals={
                L"\'ش\'",
                L"\'\\ي0041\'", // 'A'
                L"\'\\يFFFF\'", // max unicode char
                L"\'\\خ\'",
                L"\'\\ف\'",
                L"\'\\س\'",
                L"\'\\ر\'",
                L"\'\\ص\'",
                L"\'\\ج\'",
                L"\'\\\\\'", // '\\'
                L"\'\\\'\'", // '\''
                L"\'\\\"\'", // '\"'
            };
            std::vector<std::wstring> expectedTokens={
                L"\'ش\'",
                L"\'\u0041\'", // 'A'
                L"\'\uFFFF\'", // max unicode char
                L"\'\b\'",
                L"\'\t\'",
                L"\'\n\'",
                L"\'\v\'",
                L"\'\f\'",
                L"\'\r\'",
                L"\'\\\'", // '\\'
                L"\'\'\'", // '\''
                L"\'\"\'", // '\"'
            };

            THEN("Add LiteralToken::CHAR to tokens"){
                int i=0;
                for(auto &legeal:legals){
                    LexerLine lexerLine=LexerLine(legeal,i);
                    lexerLine.tokenize();
                    auto tokens=lexerLine.getTokens();
                    REQUIRE(tokens->size()==1);
                    std::shared_ptr<LexerToken> token=tokens->at(0);
                    auto literalToken=std::dynamic_pointer_cast<LiteralToken>(token);
                    REQUIRE(literalToken!=nullptr);
                    REQUIRE(literalToken->getLiteralType()==LiteralToken::CHAR);
                    REQUIRE(literalToken->getTokenType()==LexerToken::LITERAL_TOKEN);
                    REQUIRE(literalToken->getVal()==expectedTokens[i]);
                    i++;
                }
            };
        };

        WHEN("char literal has multiple characters or no characters between qoutes"){
            std::vector<std::wstring> illegals={
                L"\'حرف\'",
                L"\'\'",
                L"\'\\ي0041\\ي0042\'", // 'AB'
                L"\'\\ي000F0\'",
                L"\'\\س\\ف\'",
                L"\'\\سa\'",
            };
            THEN("Throw InvalidLengthCharacterLiteralException"){
                LexerLineTokensTestWithException<InvalidLengthCharacterLiteralException>(illegals);
            };
        };

        WHEN("line has an invalid escape sequence (in string or char literls)"){
            std::vector<std::wstring> illegals={
                L"\'\\a\'",
                L"\'\\k\'",
                L"\'\\ش\'",
                L"\"حرف\\a\"",
                L"\"حرف\\ش\"",
                L"\"حرف\\k\"",
            };
            auto msgMatcher=[](std::wstring &illegal){
                return illegal.substr(0,illegal.size()-1); // remove last qoute
            };
            THEN("Throw InvalidEscapeSequenceException"){
                LexerLineTokensTestWithException<InvalidEscapeSequenceException>(illegals,msgMatcher);
            };
        };

        WHEN("line has an invalid universal char code (in string or char literls)"){
            std::vector<std::wstring> illegals={
                L"\'\\ي\'",
                L"\'\\يF\'",
                L"\'\\يFFF\'",
                L"\'\\يFFFش\'",
                L"\'\\يش\'",
                L"\"نص\\ي\"",
                L"\"نص\\يF\"",
                L"\"نص\\يFFF\"",
                L"\"نص\\يFFFش\"",
            };
            auto msgMatcher=[](std::wstring &illegal){
                return illegal.substr(0,illegal.size()-1); // remove last qoute
            };
            THEN("Throw InvalidUniversalCharacterCodeException"){
                LexerLineTokensTestWithException<InvalidUniversalCharacterCodeException>(illegals,msgMatcher);
            };
        };

        WHEN("Misssing qoute (in string or char literls)"){
            std::vector<std::wstring> illegals={
                L"\"string literal with \\\"DOULBE QOUTES\\\"",
                L"\"",
                L"\"\\\"",
                L"\'ش",
                L"\'",
                L"\'\\\'",
            };

            THEN("Throw MissingQouteException"){
                LexerLineTokensTestWithException<MissingQouteException>(illegals);
            };
        };

        WHEN("Line is a single-line comment"){
            std::wstring line=L"// This is a single-line comment";
            auto expectedToken=LexerToken(LexerToken::COMMENT_TOKEN,line);
            THEN("Add comment token to tokens"){
                LexerLine lexerLine=LexerLine(line,1);
                lexerLine.tokenize();
                auto tokens=lexerLine.getTokens();
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
            THEN("Gives correct tokens"){
                LexerLine lexerLine=LexerLine(line,1);
                lexerLine.tokenize();
                auto tokens=lexerLine.getTokens();
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
                std::vector<NumberToken> legals={
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
                    NumberToken(NumberToken::DOUBLE,L"003.0e-2"),
                    NumberToken(NumberToken::FLOAT,L"3.00f"),
                    NumberToken(NumberToken::FLOAT,L"3.00F"),
                    NumberToken(NumberToken::FLOAT,L"03.00F"),
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
                    NumberToken(NumberToken::LONG,L"2147483648") // > INT_MAX, should be long even without suffix L
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
                for(const auto &legal:legalNumSys){
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
                std::vector<std::wstring> illegals={
                    L"12_",
                    L"3_.0",
                    L"4_e2",
                    L"4e_2",
                    L"4e2_",
                    L"15.64_e5",
                    L"15321__.166_f",
                };
                auto msgMatcher=[](std::wstring &illegal){
                    return illegal.substr(0,illegal.find(L'_')+1); // substr to first underscore
                };
                LexerLineTokensTestWithException<IllegalUnderscoreException>(illegals,msgMatcher);
            };

            THEN("Throw UnsupportedTokenException when cannot construct tokens"){
                std::vector<std::wstring> illegals={
                    L"3.0e",
                    L"3.0e+",
                    L"3.0e-",
                    L"30ef",
                    L"30.1a",
                    L"30.1e2a",
                    L"30.1e2ش",
                    L"30.1fa",
                    L"30.1fش"
                };
                LexerLineTokensTestWithException<UnsupportedTokenException>(illegals);
            };

            THEN("Throw InvalidIdentifierNameException when cannot construct tokens"){
                std::vector<std::wstring> illegals={
                    L"30a",
                    L"30ش",
                    L"30ua",
                    L"30La",
                };
                LexerLineTokensTestWithException<InvalidIdentifierNameException>(illegals);
            };

            THEN("Throw InvalidNumberSystemDigitException when different num sys digit is entered"){
                std::vector<std::wstring> illegals={
                    L"0b12",
                    L"0bm",
                    L"0o18",
                    L"0o12a",
                    L"0Om",
                    L"0xabcdefw",
                    L"0b",
                    L"0o",
                    L"0x",
                };
                LexerLineTokensTestWithException<InvalidNumberSystemDigitException>(illegals);
            };

            THEN("Throw OutOfRangeException when exceeds the maximum limits of data types"){
                std::vector<std::wstring> illegals={
                    L"3.5e38f",   // > FLOAT_MAX
                    L"1.16e-38f", // < FLOAT_MIN
                    L"1.19973e+4932", // > DOUBLE_MAX
                    L"3.3521e-4932", // < DOUBLE_MIN
                    L"9223372036854775808", // > LONG_MAX
                    L"18446744073709551616" // > ULONG_MAX
                };
                LexerLineTokensTestWithException<OutOfRangeException>(illegals);
            };
            
        };

        WHEN("line has keywords"){
            std::vector<KeywordToken> keywords={
                KeywordToken::VAR,KeywordToken::VAL,KeywordToken::FUN,KeywordToken::RETURN,
                KeywordToken::PACKAGE,KeywordToken::IMPORT,KeywordToken::CLASS,KeywordToken::INTERFACE,
                KeywordToken::OBJECT,
                KeywordToken::DATA,KeywordToken::ABSTRACT,KeywordToken::OPEN,KeywordToken::ENUM,
                KeywordToken::ANNOTATION,
                KeywordToken::PUBLIC,KeywordToken::PRIVATE,KeywordToken::PROTECTED,KeywordToken::OVERRIDE,
                KeywordToken::IF,/*KeywordToken::ELSE_IF,*/KeywordToken::ELSE,KeywordToken::WHEN,
                KeywordToken::FOR,KeywordToken::DO,KeywordToken::WHILE,KeywordToken::BREAK,KeywordToken::CONTINUE,
                KeywordToken::THROW,KeywordToken::TRY,KeywordToken::CATCH,KeywordToken::FINALLY,
                KeywordToken::TRUE,KeywordToken::FALSE
            };
            std::wstring line=L"";
            for(auto &keyword:keywords){
                line+=keyword.getVal()+L" ";
            }
            THEN("Return them as keyword tokens"){
                auto lexerLine=LexerLine(line,1);
                lexerLine.tokenize();
                auto tokens=lexerLine.getTokens();
                REQUIRE(tokens->size()==keywords.size());
                int i=0;
                for(auto &token:*tokens){
                    REQUIRE(token->operator==(keywords[i]));
                    i++;
                }
            };

        };

        WHEN("line has identifiers"){
            std::vector<std::wstring> identifiers={
                L"س",
                L"الاسم",
                L"العمر",
            };
            std::wstring line=L"";
            for(auto &identifier:identifiers){
                line+=identifier+L" ";
            }
            THEN("Return them as identifier tokens"){
                auto lexerLine=LexerLine(line,1);
                lexerLine.tokenize();
                auto tokens=lexerLine.getTokens();
                REQUIRE(tokens->size()==identifiers.size());
                int i=0;
                for(auto &token:*tokens){
                    REQUIRE(token->getVal()==identifiers[i]);
                    REQUIRE(token->getTokenType()==LexerToken::IDENTIFIER_TOKEN);
                    i++;
                }
            };

        };

        WHEN("line has different types of tokens"){
            std::wstring line=L"لو(الاختبار==\"ناجح\"){متغير س=5.23e12}";
            std::wstring lineWithSpaces=L"لو ( الاختبار == \"ناجح\" ) { متغير س = 5.23e12 }";
            std::vector<LexerToken> expectedTokens={
                KeywordToken::IF,SymbolToken::LEFT_PARENTHESIS,
                IdentifierTestToken(L"الاختبار"),
                SymbolToken::EQUAL_EQUAL,
                LiteralToken(LiteralToken::STRING,L"\"ناجح\""),
                SymbolToken::RIGHT_PARENTHESIS,
                SymbolToken::LEFT_CURLY_BRACES,
                KeywordToken::VAR,IdentifierTestToken(L"س"),SymbolToken::EQUAL,
                NumberToken(NumberToken::DOUBLE,std::to_wstring(std::stold(L"5.23e12"))),
                SymbolToken::RIGHT_CURLY_BRACES
            };
            THEN("Return correct tokens"){
                LexerLine lexerLine(line,1);
                LexerLine lexerLineWithSpaces(lineWithSpaces,1);
                lexerLine.tokenize();
                lexerLineWithSpaces.tokenize();
                auto tokens=lexerLine.getTokens();
                auto tokensWithSpaces=lexerLine.getTokens();
                REQUIRE(tokens->size()==expectedTokens.size());
                REQUIRE(tokensWithSpaces->size()==expectedTokens.size());
                int i=0;
                for(auto &expected:expectedTokens){
                    auto token1=tokens->at(i);
                    auto token2=tokensWithSpaces->at(i);
                    REQUIRE(token1->operator==(expected));
                    REQUIRE(token2->operator==(expected));
                    i++;
                }
            };
        };
    }

}