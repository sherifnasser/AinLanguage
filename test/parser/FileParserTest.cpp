#include "FileParser.hpp"
#include "LexerToken.hpp"
#include "PackageScope.hpp"
#include "FileScope.hpp"
#include "TokensIteratorForTests.hpp"
#include <catch2/catch.hpp>

TEST_CASE("Test file parser is adding file to parent package","[FileParserTest.cpp]"){
    auto package=PackageScope::AIN_PACKAGE;
    auto filePath=L"somePath";
    FileParser fp(
        getTokensIterator({LexerToken::EofToken()}),
        package,
        filePath
    );
    fp.parse();
    auto file=PackageScope::AIN_PACKAGE->findFileByPath(filePath);
    REQUIRE(file->getParentScope()==PackageScope::AIN_PACKAGE);
}