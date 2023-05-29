#pragma once
#include <iostream>
#include <memory>
#include "IAinFile.hpp"
#include "ILexer.hpp"
#include "lexerline.hpp"

class Lexer:public ILexer{
    private:
        std::shared_ptr<IAinFile> ainFile;
        std::shared_ptr<std::vector<lexerline>> lexerlines;
        
    public:
        Lexer(std::shared_ptr<IAinFile> ainFile);
        lexerline lexline(std::wstring line,int linenumber) override;
        std::vector<lexerline> getlexerlines() override;
};
