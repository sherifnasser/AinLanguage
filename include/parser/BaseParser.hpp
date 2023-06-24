#pragma once
#include "SharedPtrTypes.hpp"

template<typename T>
class BaseParser{
    protected:
        SharedTokensIterator iterator;
        SharedBaseScope scope;
    
    public:
        BaseParser<T>(
            SharedTokensIterator iterator,
            SharedBaseScope scope
        );
        virtual T parse()=0;
};

template<typename T>
BaseParser<T>::BaseParser(
    SharedTokensIterator iterator,
    SharedBaseScope scope
):iterator(iterator),scope(scope){}