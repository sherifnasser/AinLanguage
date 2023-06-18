#pragma once
#include"IExpression.hpp"

class FunCallExpression:public IExpression{
    private:
        std::wstring funName;
        SharedVector<SharedIExpression> argsExpressions;
    public:
        FunCallExpression(std::wstring &funName, SharedVector<SharedIExpression> argsExpressions);
        std::wstring evaluate(SharedScope evalScope) override;
        void print(std::wstring tabsize=L"") override;
};