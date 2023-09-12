#pragma once
#include "BaseParser.hpp"
#include "ParserProvidersAliases.hpp"
#include "SharedPtrTypes.hpp"
class ClassParser:public BaseParser<SharedClassScope>{
    private:
        FunParserProvider funParserProvider;
        VarStmParserProvider varStmParserProvider;
        enum class VisibilityModifier{
            NOT_PARSED,PUBLIC,PRIVATE
        };
        VisibilityModifier visibility;
        void resetVisibility();
        void parseVisibility();
        void parseFunScope(SharedClassScope parentScope);
        void parseVarStm(SharedClassScope parentScope);
    public:
        ClassParser(
            SharedTokensIterator iterator,
            SharedBaseScope scope,
            FunParserProvider funParserProvider,
            VarStmParserProvider varStmParserProvider
        );
        SharedClassScope parse()override;
};