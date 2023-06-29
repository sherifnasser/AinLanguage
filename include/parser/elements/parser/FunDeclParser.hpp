#pragma once
#include "BaseParser.hpp"
#include "SharedPtrTypes.hpp"
class FunDeclParser:public BaseParser<SharedFunDecl>{
    private:
        bool mustHaveExplicitReturnType;
    public:
        FunDeclParser(
            SharedTokensIterator iterator,
            SharedBaseScope scope,
            bool mustHaveExplicitReturnType=false
        );
        SharedFunDecl parse()override;
};