#include "FileParser.hpp"
#include "PackageParser.hpp"
#include "PackageScope.hpp"
#include "FileScope.hpp"
#include "SharedPtrTypes.hpp"
#include <memory>

FileParser::FileParser(
    SharedTokensIterator iterator,
    std::wstring filePath,
    SharedBaseParser<SharedPackageScope> packageParser
):BaseParser(iterator,nullptr),filePath(filePath),packageParser(packageParser){}


SharedFileScope FileParser::parse(){
    auto package=packageParser->parse();
    auto file=std::make_shared<FileScope>(filePath,package);
    package->addFile(file);
    return file;
}

std::wstring FileParser::getFilePath(){
    return filePath;
}