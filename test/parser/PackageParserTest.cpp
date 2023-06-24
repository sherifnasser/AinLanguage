#include "PackageParser.hpp"
#include "SharedPtrTypes.hpp"
#include "LexerToken.hpp"
#include "LinkedList.hpp"
#include "SymbolToken.hpp"
#include "KeywordToken.hpp"
#include "TokensIterator.hpp"
#include "PackageScope.hpp"
#include "UnexpectedTokenException.hpp"
#include <catch2/catch.hpp>
#include <memory>
#include <string>

TEST_CASE("Test package parser","[PackageParserTest.cpp]"){
    auto eol=std::make_shared<LexerToken>(LexerToken(LexerToken::EOL_TOKEN,L""));
    auto eof=std::make_shared<LexerToken>(LexerToken(LexerToken::EOF_TOKEN,L""));
    auto packageKeyword=std::make_shared<LexerToken>(KeywordToken::PACKAGE);
    auto dot=std::make_shared<LexerToken>(SymbolToken::DOT);
    auto comma=std::make_shared<LexerToken>(SymbolToken::COMMA);
    auto package1=std::make_shared<LexerToken>(LexerToken(LexerToken::IDENTIFIER_TOKEN,L"حزمة1"));
    auto package2=std::make_shared<LexerToken>(LexerToken(LexerToken::IDENTIFIER_TOKEN,L"حزمة2"));
    LinkedList<SharedLexerToken> list;
    

    SECTION("no packages keyword in iterator, will return Ain package"){

        auto iterator=std::make_shared<TokensIterator>(list);

        auto parser=std::make_shared<PackageParser>(iterator,PackageScope::AIN_PACKAGE);

        auto returnedPackage=parser->parse();

        REQUIRE(returnedPackage==PackageScope::AIN_PACKAGE);
    };

    SECTION("when there is package keyword"){
        list.insert(packageKeyword);
        list.insert(package1);
        list.insert(dot);
        list.insert(package2);
        list.insert(eol);

        auto iterator=std::make_shared<TokensIterator>(list);

        auto parser=std::make_shared<PackageParser>(iterator,PackageScope::AIN_PACKAGE);

        auto returnedPackage=parser->parse();
        auto returnedPackageParent=std::dynamic_pointer_cast<PackageScope>(
            returnedPackage->getParentScope()
        );
        auto returnedPackageParentParent=std::dynamic_pointer_cast<PackageScope>(
            returnedPackageParent->getParentScope()
        );
        REQUIRE(
            returnedPackageParentParent
            ==
            PackageScope::AIN_PACKAGE
        );
        REQUIRE(
            returnedPackageParent
            ==
            PackageScope::AIN_PACKAGE
            ->findPackageByName(package1->getVal())
        );
        REQUIRE(
            returnedPackage
            ==
            PackageScope::AIN_PACKAGE
            ->findPackageByName(package1->getVal())
            ->findPackageByName(package2->getVal())
        );
    };

    SECTION("Testing when unexpected token is after dot after package name"){
        
        list.insert(eol);
        list.insert(packageKeyword);
        list.insert(package1);
        list.insert(dot);
        list.insert(packageKeyword);
        list.insert(eol);

        auto iterator=std::make_shared<TokensIterator>(list);

        auto parser=std::make_shared<PackageParser>(iterator,PackageScope::AIN_PACKAGE);

        auto matcher=Catch::Matchers::Predicate<UnexpectedTokenException>(
            [&](UnexpectedTokenException e){
                auto npos=std::wstring::npos;
                auto hasIdentifier=e.whatWstr().find(
                    LexerToken::stringify(LexerToken::IDENTIFIER_TOKEN)
                );
                auto hasKeyword=e.whatWstr().find(
                    LexerToken::stringify(LexerToken::KEYWORD_TOKEN)
                );
                auto lineNumberMatches=e.lineNumber==2;
                return lineNumberMatches&&hasIdentifier!=npos&&hasKeyword!=npos;
            }
        );
        REQUIRE_THROWS_MATCHES(
            parser->parse(),
            UnexpectedTokenException,
            matcher
        );

    };

}