#pragma once
#include"IOldExpression.hpp"

class StringExpression:public IOldExpression{
    private:
        std::wstring val;
    public:
        StringExpression(std::wstring &val);
        std::wstring evaluate(SharedScope evalScope) override;
        void print(std::wstring tabsize=L"") override;
};