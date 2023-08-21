#pragma once
#include "BaseParser.hpp"
#include "ParserProvidersAliases.hpp"
#include "SharedPtrTypes.hpp"
class ClassParser:public BaseParser<SharedClassScope>{
    private:
        FunParserProvider funParserProvider;
        VarStmParserProvider varStmParserProvider;
        enum class VisibilityModifier{
            PUBLIC,PRIVATE
        };
        VisibilityModifier parseVisibility();
        void parseFunScope(VisibilityModifier visibility,SharedClassScope parentScope);
        void parseVarStm(VisibilityModifier visibility,SharedClassScope parentScope);
    public:
        ClassParser(
            SharedTokensIterator iterator,
            SharedBaseScope scope,
            FunParserProvider funParserProvider,
            VarStmParserProvider varStmParserProvider
        );
        SharedClassScope parse()override;
};