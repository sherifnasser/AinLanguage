#pragma once
#include "BaseParser.hpp"
#include "SharedPtrTypes.hpp"
class FileParser:public BaseParser<SharedFileScope>{
    private:
        std::wstring filePath;
        SharedBaseParser<SharedPackageScope> packageParser;
    public:
        FileParser(
            SharedTokensIterator iterator,
            std::wstring filePath,
            SharedBaseParser<SharedPackageScope> packageParser
        );
        SharedFileScope parse();

        std::wstring getFilePath();
        
};