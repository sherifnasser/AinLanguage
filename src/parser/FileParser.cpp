#include "FileParser.hpp"
#include "PackageParser.hpp"
#include "PackageScope.hpp"
#include "FileScope.hpp"
#include "SharedPtrTypes.hpp"
#include <memory>
FileParser::FileParser(
    SharedTokensIterator iterator,
    SharedPackageScope scope,
    std::wstring filePath
):BaseParser(iterator,scope),filePath(filePath){}


SharedFileScope FileParser::parse(){
    PackageParser pp(iterator,scope);
    auto package=pp.parse();
    auto file=std::make_shared<FileScope>(filePath,package);
    package->addFile(file);
    return file;
}

std::wstring FileParser::getFilePath(){
    return filePath;
}
