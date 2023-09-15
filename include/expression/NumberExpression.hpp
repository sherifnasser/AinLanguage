#pragma once
#include"IOldExpression.hpp"

class NumberExpression:public IOldExpression{
    private:
        std::wstring val;
    public:
        NumberExpression(std::wstring &val);
        std::wstring evaluate(SharedScope evalScope) override;
        void print(std::wstring tabsize=L"") override;
};