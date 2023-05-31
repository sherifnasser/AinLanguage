#pragma once
#include <iostream>
#include "LexerToken.hpp"

class LiteralToken:public LexerToken
{
    public:
        enum LITERAL_TYPE : int{
            STRING=0,
            NUMBER=1,
            BOOL=2
        };

        LiteralToken(LITERAL_TYPE literalType,std::wstring val);
        LITERAL_TYPE getLiteralType();
    private:
        LITERAL_TYPE literalType;
        std::wstring val;
};