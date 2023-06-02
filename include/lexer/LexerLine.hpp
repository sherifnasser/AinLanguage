#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "LexerToken.hpp"

class LexerLine{
    private:
        std::shared_ptr<std::vector<std::shared_ptr<LexerToken>>> tokens;
        std::wstring line;
        int lineNumber;
        bool isNotNullToken(std::shared_ptr<LexerToken> token);
        std::shared_ptr<LexerToken> findStringLiteralToken(int* startIndex);
        std::shared_ptr<LexerToken> findCommentToken(int* startIndex);
        std::shared_ptr<LexerToken> findSymbolToken(int* startIndex);
    public:
        LexerLine(std::wstring &line,int lineNumber);
        void tokenize();
        std::shared_ptr<std::vector<std::shared_ptr<LexerToken>>> getTokens();
        int getLineNumber();
};
