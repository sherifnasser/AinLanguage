#pragma once
#include "SharedPtrTypes.hpp"

class ILexer{
        
    public:
        virtual SharedVector<SharedILexerLine> getLexerLines()=0;
        virtual SharedVector<SharedLexerToken> getTokens()=0;
};