#pragma once
#include"IExpression.hpp"

class NumberExpression:public IExpression{
    private:
        std::wstring val;
    public:
        NumberExpression(std::wstring &val);
        std::wstring evaluate(SharedScope evalScope) override;
        void print(std::wstring tabsize=L"") override;
};