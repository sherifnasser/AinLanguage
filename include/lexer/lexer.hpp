#pragma once
#include <iostream>
#include "ain_file.hpp"
#include "lexerline.hpp"

class lexer{
    private:
        AinFile ainFile;
        std::vector<lexerline>* lexerlines;
        
    public:
        lexer(AinFile ainFile);
        std::vector<lexerline> getlexerlines();
};
