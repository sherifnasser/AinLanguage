#pragma once
#include <iostream>
#include "AinFile.hpp"
#include "lexerline.hpp"

class lexer{
    private:
        AinFile ainFile;
        std::vector<lexerline>* lexerlines;
        
    public:
        lexer(AinFile ainFile);
        lexerline lexline(std::wstring line,int linenumber);
        std::vector<lexerline> getlexerlines();
};
