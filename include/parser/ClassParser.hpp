#pragma once
#include "BaseParser.hpp"
#include "ParserProvidersAliases.hpp"
#include "SharedPtrTypes.hpp"
class ClassParser:public BaseParser<SharedClassScope>{
    private:
        FunParserProvider funParserProvider;
        enum class VisibilityModifier{
            PUBLIC,PRIVATE
        };
        void parseFunScope(VisibilityModifier visibility,SharedClassScope parentScope);
    public:
        ClassParser(
            SharedTokensIterator iterator,
            SharedBaseScope scope,
            FunParserProvider funParserProvider
        );
        SharedClassScope parse()override;
};