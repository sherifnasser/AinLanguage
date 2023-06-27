#pragma once
#include"IExpression.hpp"

class OldVariableAccessExpression:public IExpression{
    private:
        std::wstring name;
    public:
        OldVariableAccessExpression(std::wstring &name);
        std::wstring evaluate(SharedScope evalScope) override;
        void print(std::wstring tabsize=L"") override;
};