#pragma once
#include "BaseParser.hpp"
#include "ParserProvidersAliases.hpp"
#include "SharedPtrTypes.hpp"

class FunDeclParser:public BaseParser<SharedFunDecl>{
    private:
        SharedBaseParser<SharedType> returnTypeParser;
        SharedBaseParser<SharedFunParamater> paramsParser;
    public:
        FunDeclParser(
            SharedTokensIterator iterator,
            SharedBaseScope scope,
            TypeParserProvider typeParserProvider,
            FunParamaterParserProvider paramsParserProvider
        );
        SharedFunDecl parse()override;
};