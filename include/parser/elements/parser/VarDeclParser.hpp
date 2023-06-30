#pragma once
#include "BaseParser.hpp"
#include "SharedPtrTypes.hpp"
class VarDeclParser:public BaseParser<SharedVarDecl>{
    public:
        VarDeclParser(
            SharedTokensIterator iterator,
            SharedBaseScope scope
        );
        SharedVarDecl parse()override;
};