#define CATCH_CONFIG_MAIN
#include <vector>
#include "LexerToken.hpp"
#include "SharedPtrTypes.hpp"
#include <iostream>
#include <memory>
#include <catch2/catch.hpp>
#include "Lexer.hpp"
#include "LinkedList.hpp"

class FakeAinFileWithDelimitedComments: public IAinFile{
    public:
        void readAinFile(std::string& path) override{}

        std::vector<std::wstring> getLines() override{
            return {
                L"/*line0/*",
                L"/*line1*/*/",
                L"  line2*/",
                L"//line3 /*",
                L"/*line4",
                L"  line5*/id/*",
                L"*/line6",
            };
        }
};

SCENARIO("Test Lexer","[LexerTest.cpp]"){
    
    WHEN("File has delimited comments"){
        THEN("Ignore them"){
            auto file=std::make_shared<FakeAinFileWithDelimitedComments>();
            Lexer lexer(file);
            auto tokens=lexer.getTokens();
            auto lines=file->getLines();
            std::vector<LexerToken> expectedTokens={
                LexerToken(LexerToken::COMMENT_TOKEN,lines[0]),
                LexerToken::EolToken(),
                LexerToken(LexerToken::COMMENT_TOKEN,lines[1]),
                LexerToken::EolToken(),
                LexerToken(LexerToken::COMMENT_TOKEN,lines[2]),
                LexerToken::EolToken(),
                LexerToken(LexerToken::COMMENT_TOKEN,lines[3]),
                LexerToken::EolToken(),
                LexerToken(LexerToken::COMMENT_TOKEN,lines[4]),
                LexerToken::EolToken(),
                LexerToken(LexerToken::COMMENT_TOKEN,L"  line5*/"),
                LexerToken::IdentifierToken(L"id"),
                LexerToken(LexerToken::COMMENT_TOKEN,L"/*"),
                LexerToken::EolToken(),
                LexerToken(LexerToken::COMMENT_TOKEN,L"*/"),
                LexerToken::IdentifierToken(L"line6"),
                LexerToken::EolToken(),
                LexerToken::EofToken()
            };

            REQUIRE(tokens->size==expectedTokens.size());
            tokens->forEachIndexed([=](SharedLexerToken token,int i){
                auto expectedToken=expectedTokens[i];
                REQUIRE(token->operator==(expectedToken));
            });
            REQUIRE(tokens->tail->val->getTokenType()==LexerToken::EOF_TOKEN);
        }
    }
}