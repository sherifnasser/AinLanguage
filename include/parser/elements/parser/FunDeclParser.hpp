#pragma once
#include "BaseParser.hpp"
#include "SharedPtrTypes.hpp"
class FunDeclParser:public BaseParser<SharedFunDecl>{
    private:
        bool defaultReturnTypeIsUnit;
    public:
        FunDeclParser(
            SharedTokensIterator iterator,
            SharedBaseScope scope,
            bool defaultReturnTypeIsUnit=false
        );
        SharedFunDecl parse()override;
};