#include "FileParser.hpp"
#include "LexerToken.hpp"
#include "PackageScope.hpp"
#include "FileScope.hpp"
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
}

TEST_CASE("Test file parser is adding file to parent package","[FileParserTest.cpp]"){
    auto filePath=L"somePath";
    auto fakePackageParser=std::make_shared<FakePackageParser>();
    auto parsedPackage=fakePackageParser->parse();
    FileParser fp(
        getTokensIterator({LexerToken::EofToken()}),
        filePath,
        fakePackageParser
    );
    fp.parse();

    auto file=parsedPackage->findFileByPath(filePath);
    REQUIRE(file->getParentScope()==PackageScope::AIN_PACKAGE);
}