#include "FileParser.hpp"
#include "BaseParser.hpp"
#include "LexerToken.hpp"
#include "PackageScope.hpp"
#include "FileScope.hpp"
#include "PrintlnFunScope.hpp"
#include "SharedPtrTypes.hpp"
#include "TokensIteratorForTests.hpp"
#include <catch2/catch.hpp>
#include <memory>

namespace{
    struct FakePackageParser:public BaseParser<SharedPackageScope>{
        FakePackageParser():BaseParser(nullptr,nullptr){}
        SharedPackageScope parse() override{
            return PackageScope::AIN_PACKAGE;
        }
    };

    struct FakeFunParser:public BaseParser<SharedFunScope>{
        FakeFunParser():BaseParser(nullptr,nullptr){}
        SharedFunScope parse() override{
            return std::make_shared<PrintlnFunScope>();
        }
    };
}

TEST_CASE("Test file parser is adding file to parent package","[FileParserTest.cpp]"){
    auto filePath=L"somePath";
    auto fakePackageParser=std::make_shared<FakePackageParser>();
    auto fakeFunParser=std::make_shared<FakeFunParser>();
    auto fakeFunParserProvider=[&](SharedTokensIterator,SharedBaseScope){
        return fakeFunParser;
    };
    auto parsedPackage=fakePackageParser->parse();
    FileParser fp(
        getTokensIterator({LexerToken::EofToken()}),
        filePath,
        fakePackageParser,
        fakeFunParserProvider
    );
    fp.parse();

    auto file=parsedPackage->findFileByPath(filePath);
    REQUIRE(file->getParentScope()==PackageScope::AIN_PACKAGE);
}