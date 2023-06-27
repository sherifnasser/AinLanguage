#pragma once
#include "BaseParser.hpp"
#include "SharedPtrTypes.hpp"
class TypeParser:public BaseParser<SharedType>{
    public:
        TypeParser(SharedTokensIterator iterator);
        SharedType parse()override;
};