#pragma once
#include "LexerToken.hpp"

class BadToken:public LexerToken
{
    public:
        BadToken():LexerToken(BAD_TOKEN,L""){}
};