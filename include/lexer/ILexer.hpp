#pragma once
#include <iostream>
#include "lexerline.hpp"

class ILexer{
        
    public:
        virtual lexerline lexline(std::wstring line,int linenumber)=0;
        virtual std::vector<lexerline> getlexerlines()=0;
};
