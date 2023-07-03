#include "LexerToken.hpp"
#include "SharedPtrTypes.hpp"
#include "TokensIteratorForTests.hpp"
#include "TypeChecker.hpp"
#include "PackageScope.hpp"
#include "FileScope.hpp"
#include "Type.hpp"
#include "TypeParser.hpp"
#include "UnexpectedTokenException.hpp"
#include <catch2/catch.hpp>
#include <memory>
#include <vector>

struct FakeTypeChecker:public Semantics::ITypeChecker{
    int calledTimes=0;
    
    void subscribe(int lineNumber,SharedBaseScope searchScope,SharedType type)override{
        calledTimes++;
    }

    void check()override{};
};

TEST_CASE("TypeParser tests","[TypeParserTest.cpp]"){

    auto fakeTypeChecker=std::make_shared<FakeTypeChecker>();

    auto scope = std::make_shared<FileScope>(L"Test",PackageScope::AIN_PACKAGE);

    auto iterator=getTokensIterator({
        LexerToken::IdentifierToken(
            *Type::INT->getName()
        )
    });

    SECTION("parsing a type"){
        TypeParser parser(iterator,scope,fakeTypeChecker);

        auto type=parser.parse();

        REQUIRE(*type==*Type::INT);
        REQUIRE(fakeTypeChecker->calledTimes==1);
        /*TODO test with generic and nullable types*/
    }
    
    SECTION("Throw UnexpectedTokenException when calling parse without providing an identifier for the type"){
        TypeParser parser(getTokensIterator({}),scope,fakeTypeChecker);

        REQUIRE(fakeTypeChecker->calledTimes==0);
        REQUIRE_THROWS_AS(parser.parse(), UnexpectedTokenException);
    }
}