#pragma once
#include <iostream>
#include <memory>
#include "IAinFile.hpp"
#include "ILexer.hpp"
#include "LexerLine.hpp"

class Lexer:public ILexer{
    private:
        std::shared_ptr<IAinFile> ainFile;
        std::shared_ptr<std::vector<LexerLine>> lexerlines;
        
    public:
        Lexer(std::shared_ptr<IAinFile> ainFile);
        LexerLine lexLine(std::wstring line,int linenumber) override;
        std::vector<LexerLine> getLexerLines() override;
};
