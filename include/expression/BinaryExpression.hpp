#pragma once
#include"IExpression.hpp"

class BinaryExpression:public IExpression{
    private:
        SharedIExpression left;
        SharedLexerToken operation;
        SharedIExpression right;
    public:
        BinaryExpression(SharedIExpression left, SharedLexerToken operation, SharedIExpression right);
        std::wstring evaluate(SharedScope evalScope) override;
        void print(std::wstring tabsize=L"") override;
        std::wstring evaluatelogicalor(std::wstring l, std::wstring r);
        std::wstring evaluatelogicaland(std::wstring l, std::wstring r);
        std::wstring evaluateequalequal(std::wstring l, std::wstring r);
        std::wstring evaluatenotequal(std::wstring l, std::wstring r);
        std::wstring evaluategreaterequal(std::wstring l, std::wstring r);
        std::wstring evaluatelessequal(std::wstring l, std::wstring r);
        std::wstring evaluategreater(std::wstring l, std::wstring r);
        std::wstring evaluateless(std::wstring l, std::wstring r);
        std::wstring evaluateplus(std::wstring l, std::wstring r);
        std::wstring evaluateminus(std::wstring l, std::wstring r);
        std::wstring evaluatestar(std::wstring l, std::wstring r);
        std::wstring evaluateslash(std::wstring l, std::wstring r);
        std::wstring evaluatemodulo(std::wstring l, std::wstring r);
        std::wstring evaluatepower(std::wstring l, std::wstring r);
};