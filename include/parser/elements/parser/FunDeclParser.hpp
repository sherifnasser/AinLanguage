#pragma once
#include "BaseParser.hpp"
#include "SharedPtrTypes.hpp"
class FunDeclParser:public BaseParser<SharedFunDecl>{
    public:
        FunDeclParser(
            SharedTokensIterator iterator,
            SharedBaseScope scope
        );
        SharedFunDecl parse()override;
};