#pragma once
#include "BaseParser.hpp"
#include "SharedPtrTypes.hpp"
class FunParamaterParser:public BaseParser<SharedFunParamater>{
    public:
        FunParamaterParser(SharedTokensIterator iterator);
        SharedFunParamater parse()override;
};