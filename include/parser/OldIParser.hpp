#pragma once
#include "SharedPtrTypes.hpp"
class IParser
{
public:
    virtual void startParse(SharedLinkedList<SharedLexerToken> tokens,SharedGlobalScope globalScope)=0;
};