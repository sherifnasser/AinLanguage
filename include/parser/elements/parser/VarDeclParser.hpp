#pragma once
#include "BaseParser.hpp"
#include "SharedPtrTypes.hpp"
class VarDeclParser:public BaseParser<SharedVarDecl>{
    private:
        bool typeFromExpression;
    public:
        VarDeclParser(
            SharedTokensIterator iterator,
            SharedBaseScope scope,
            bool typeFromExpression=false
        );
        SharedVarDecl parse()override;
};