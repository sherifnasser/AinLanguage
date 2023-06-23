#pragma once
#include "LexerToken.hpp"

class EOFToken:public LexerToken
{
    public:
        EOFToken():LexerToken(EOF_TOKEN,L""){}
};