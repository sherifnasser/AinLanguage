#pragma once
#include "BaseParser.hpp"
#include "ParserProvidersAliases.hpp"
#include "SharedPtrTypes.hpp"
class FileParser:public BaseParser<SharedFileScope>{
    private:
        std::wstring filePath;
        SharedBaseParser<SharedPackageScope> packageParser;
        FunParserProvider funParserProvider;
        ClassParserProvider classParserProvider;
    public:
        FileParser(
            SharedTokensIterator iterator,
            std::wstring filePath,
            SharedBaseParser<SharedPackageScope> packageParser,
            FunParserProvider funParserProvider,
            ClassParserProvider classParserProvider
        );
        SharedFileScope parse();

        std::wstring getFilePath();
        
};