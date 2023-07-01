#pragma once
#include"IOldExpression.hpp"

class FunCallExpression:public IOldExpression{
    private:
        std::wstring funName;
        SharedVector<SharedIOldExpression> argsExpressions;
    public:
        FunCallExpression(std::wstring &funName, SharedVector<SharedIOldExpression> argsExpressions);
        std::wstring evaluate(SharedScope evalScope) override;
        void print(std::wstring tabsize=L"") override;
};