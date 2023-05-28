#pragma once
#include <iostream>
#include <memory>
#include "IAinFile.hpp"
#include "lexerline.hpp"

class Lexer{
    private:
        std::shared_ptr<IAinFile> ainFile;
        std::vector<lexerline>* lexerlines;
        
    public:
        Lexer(std::shared_ptr<IAinFile> ainFile);
        lexerline lexline(std::wstring line,int linenumber);
        std::vector<lexerline> getlexerlines();
};
