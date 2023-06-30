#include "StringMaker.hpp"
#include <memory>
#include <string>
#include <vector>
#include "ConflictingDeclarationException.hpp"
#include "FileScope.hpp"
#include "FunDeclParser.hpp"
#include "FunParamater.hpp"
#include "FunDecl.hpp"
#include "KeywordToken.hpp"
#include "LexerToken.hpp"
#include "OperatorFunShouldHaveSingleParamException.hpp"
#include "PackageScope.hpp"
#include "SharedPtrTypes.hpp"
#include "SymbolToken.hpp"
#include "TypeParser.hpp"
#include "TokensIteratorForTests.hpp"
#include "UnexpectedTokenException.hpp"

TEST_CASE("FunDeclParser tests", "[FunDeclParserTest.cpp]"){
    auto FUN_NAME=LexerToken::IdentifierToken(L"الجمع");
    auto PARAM_NAME=LexerToken::IdentifierToken(L"رقم");
    auto PARAM_NAME2=LexerToken::IdentifierToken(L"2رقم");
    auto INT_TYPE_NAME=LexerToken::IdentifierToken(
        *Type::INT->name
    );
    auto DOUBLE_TYPE_NAME=LexerToken::IdentifierToken(
        *Type::DOUBLE->name
    );

    auto scope = std::make_shared<FileScope>(L"Test",PackageScope::AIN_PACKAGE);


    SECTION("parse function declaration"){
        std::vector<LexerToken> tokens={
            KeywordToken::FUN,
            FUN_NAME,
            SymbolToken::LEFT_PARENTHESIS,
            PARAM_NAME,
            SymbolToken::COLON,
            INT_TYPE_NAME,
            SymbolToken::COMMA,
            PARAM_NAME2,
            SymbolToken::COLON,
            DOUBLE_TYPE_NAME,
            SymbolToken::COMMA,
            SymbolToken::RIGHT_PARENTHESIS
        };

        auto parse=[&](){
            auto iterator=getTokensIterator(tokens);

            FunDeclParser parser(iterator, scope);

            auto result=parser.parse();

            REQUIRE(result != nullptr);

            REQUIRE(*result->name == FUN_NAME.getVal());
            REQUIRE(*result->isOperator == false);
            REQUIRE(result->params->size() == 2);
            REQUIRE(*result->params->at(0)->name == PARAM_NAME.getVal());
            REQUIRE(*result->params->at(0)->type==*Type::INT);
            REQUIRE(*result->params->at(1)->name == PARAM_NAME2.getVal());
            REQUIRE(*result->params->at(1)->type==*Type::DOUBLE);
            return result;
        };

        SECTION("with implicit return type"){
            auto result=parse();
            REQUIRE(result->hasImplicitReturnType());
        }

        SECTION("with explicit return type") {
            tokens.push_back(SymbolToken::COLON);
            tokens.push_back(DOUBLE_TYPE_NAME);
            auto result=parse();
            REQUIRE_FALSE(result->hasImplicitReturnType());
            REQUIRE(*result->returnType == *Type::DOUBLE);
        }
    }

    SECTION("parse operator function declaration") {
        auto iterator=getTokensIterator({
            KeywordToken::FUN,
            KeywordToken::OPERATOR,
            FUN_NAME,
            SymbolToken::LEFT_PARENTHESIS,
            PARAM_NAME,
            SymbolToken::COLON,
            INT_TYPE_NAME,
            SymbolToken::RIGHT_PARENTHESIS,
            SymbolToken::COLON,
            DOUBLE_TYPE_NAME
        });

        FunDeclParser parser(iterator, scope);

        auto result = parser.parse();

        REQUIRE(result != nullptr);
        REQUIRE(*result->name == FUN_NAME.getVal());
        REQUIRE(*result->returnType == *Type::DOUBLE);
        REQUIRE(*result->isOperator == true);
        REQUIRE(result->params->size() == 1);
        REQUIRE(*result->params->at(0)->name == PARAM_NAME.getVal());
        REQUIRE(*result->params->at(0)->type==*Type::INT);
    }

    SECTION("throw OperatorFunShouldHaveSingleParamException if operator function has more than one parameter") {
        auto iterator=getTokensIterator({
            KeywordToken::FUN,
            KeywordToken::OPERATOR,
            FUN_NAME,
            SymbolToken::LEFT_PARENTHESIS,
            PARAM_NAME,
            SymbolToken::COLON,
            INT_TYPE_NAME,
            SymbolToken::COMMA,
            PARAM_NAME2,
            SymbolToken::COLON,
            INT_TYPE_NAME,
            SymbolToken::RIGHT_PARENTHESIS,
            SymbolToken::COLON,
            DOUBLE_TYPE_NAME
        });

        FunDeclParser parser(iterator, scope);

        REQUIRE_THROWS_AS(parser.parse(), OperatorFunShouldHaveSingleParamException);
    }

    SECTION("throw ConflictingDeclarationException if function parameters have the same name") {
        auto iterator=getTokensIterator({
            KeywordToken::FUN,
            FUN_NAME,
            SymbolToken::LEFT_PARENTHESIS,
            PARAM_NAME,
            SymbolToken::COLON,
            INT_TYPE_NAME,
            SymbolToken::COMMA,
            PARAM_NAME,
            SymbolToken::COLON,
            DOUBLE_TYPE_NAME,
            SymbolToken::RIGHT_PARENTHESIS,
            SymbolToken::COLON,
            DOUBLE_TYPE_NAME
        });

        FunDeclParser parser(iterator, scope);

        REQUIRE_THROWS_AS(parser.parse(), ConflictingDeclarationException);
    }

    SECTION("throw UnexpectedTokenException if one of tokens is missing"){
        std::vector<LexerToken> trueDecl={
            KeywordToken::FUN,
            FUN_NAME,
            SymbolToken::LEFT_PARENTHESIS,
            PARAM_NAME,
            SymbolToken::COLON,
            INT_TYPE_NAME,
            SymbolToken::COMMA,
            PARAM_NAME2,
            SymbolToken::COLON,
            DOUBLE_TYPE_NAME,
            SymbolToken::RIGHT_PARENTHESIS,
            LexerToken::EolToken()
        };

        std::vector<int> missingTokensIndicies={
            1,  // FUN_NAME
            2,  // SymbolToken::LEFT_PARENTHESIS,
            3,  // PARAM_NAME,
            4,  // SymbolToken::COLON,
            5,  // INT_TYPE_NAME,
            6,  // SymbolToken::COMMA,
            10, // SymbolToken::RIGHT_PARENTHESIS
        };

        auto removeAndAssert=[&](int missingTokenIndex){

            auto invalidDecl=trueDecl;

            invalidDecl.erase(invalidDecl.begin() + missingTokenIndex);

            auto iterator=getTokensIterator(invalidDecl);

            FunDeclParser parser(iterator, scope);

            REQUIRE_THROWS_AS(parser.parse(), UnexpectedTokenException);

        };

        for(auto missingTokenIndex:missingTokensIndicies){
            removeAndAssert(missingTokenIndex);
        }

        SECTION("has explicit return type and no type provided after colon"){
            trueDecl.push_back(SymbolToken::COLON);
            trueDecl.push_back(INT_TYPE_NAME);
            trueDecl.push_back(LexerToken::EofToken());
            removeAndAssert(13); // index of fun return type token
        }
       
    }

}