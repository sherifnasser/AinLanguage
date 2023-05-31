#pragma once
#include <iostream>
#include "LexerLine.hpp"

class ILexer{
        
    public:
        virtual LexerLine lexLine(std::wstring line,int linenumber)=0;
        virtual std::vector<LexerLine> getLexerLines()=0;
};
