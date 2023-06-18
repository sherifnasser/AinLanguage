#pragma once
#include"IExpression.hpp"

class StringExpression:public IExpression{
    private:
        std::wstring val;
    public:
        StringExpression(std::wstring &val);
        std::wstring evaluate(SharedScope evalScope) override;
        void print(std::wstring tabsize=L"") override;
};