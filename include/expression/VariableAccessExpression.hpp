#pragma once
#include"IExpression.hpp"

class VariableAccessExpression:public IExpression{
    private:
        std::wstring name;
    public:
        VariableAccessExpression(std::wstring &name);
        std::wstring evaluate(SharedScope evalScope) override;
        void print(std::wstring tabsize=L"") override;
};