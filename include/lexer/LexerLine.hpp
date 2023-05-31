#pragma once
#include <iostream>
#include <vector>
#include "LexerToken.hpp"

class LexerLine{
    private:
        std::shared_ptr<std::vector<std::shared_ptr<LexerToken>>> tokens;
        std::wstring line;
        int lineNumber;
        int findStringLiteralToken(int startIndex);
        int findSymbolToken(int startIndex);
    public:
        LexerLine(std::wstring &line,int lineNumber);
        void tokenize();
        std::shared_ptr<std::vector<std::shared_ptr<LexerToken>>> getTokens();
        int getLineNumber();
};
