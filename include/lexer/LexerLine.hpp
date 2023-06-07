#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "LexerToken.hpp"
#include "NumberToken.hpp"

class LexerLine{
    private:
        enum NUM_SYS{
            DEC=10,
            BIN=2,
            OCT=8,
            HEX=16,
        };
        std::shared_ptr<std::vector<std::shared_ptr<LexerToken>>> tokens;
        std::wstring line;
        int lineNumber;
        bool isNotNullToken(std::shared_ptr<LexerToken> token);
        std::shared_ptr<LexerToken> findStringLiteralToken(int* startIndex);
        std::shared_ptr<LexerToken> findCommentToken(int* startIndex);
        std::shared_ptr<LexerToken> findSymbolToken(int* startIndex);
        std::shared_ptr<LexerToken> findNumberToken(int* startIndex);
        std::shared_ptr<LexerToken> findIdentifierOrKeywordToken(int* startIndex);
        void skipAfterNonDecIntDigitArray(int* startIndex,NUM_SYS numSys);
        NumberToken::NUMBER_TYPE skipAfterDecDigitArray(int* startIndex);
        void skipAfterDigitArray(int* startIndex,int* absoluteStartIndex,NUM_SYS numSys=NUM_SYS::DEC); // Default is decimal
        void getIntNumberToken(int *startIndex,std::wstring* number,NumberToken::NUMBER_TYPE* numType,NUM_SYS numSys);
        void getDoubleNumberToken(std::wstring* number);
        void getFloatNumberToken(std::wstring* number);
    public:
        LexerLine(std::wstring &line,int lineNumber);
        void tokenize();
        std::shared_ptr<std::vector<std::shared_ptr<LexerToken>>> getTokens();
        int getLineNumber();
};
