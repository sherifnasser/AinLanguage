#pragma once
#include "BaseParser.hpp"
#include "SharedPtrTypes.hpp"
class FileParser:public BaseParser<SharedFileScope>{
    private:
        std::wstring filePath;
    public:
        FileParser(
            SharedTokensIterator iterator,
            SharedPackageScope scope,
            std::wstring filePath
        );
        SharedFileScope parse();

        std::wstring getFilePath();
        
};