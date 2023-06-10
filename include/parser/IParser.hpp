#pragma once
#include "SharedPtrTypes.hpp"
class IParser
{
public:
    virtual void startParse(SharedVector<SharedLexerToken> tokens,SharedGlobalScope globalScope)=0;
};