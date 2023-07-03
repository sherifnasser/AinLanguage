#pragma once
#include "BaseParser.hpp"
#include "ParserProvidersAliases.hpp"
#include "SharedPtrTypes.hpp"
class FunParamaterParser:public BaseParser<SharedFunParamater>{
    private:
        SharedBaseParser<SharedType> typeParser;
    public:
        FunParamaterParser(
            SharedTokensIterator iterator,
            SharedBaseScope scope,
            TypeParserProvider typeParserProvider
        );
        SharedFunParamater parse()override;
};