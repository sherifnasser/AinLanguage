#pragma once
#include"IOldExpression.hpp"

class OldVariableAccessExpression:public IOldExpression{
    private:
        std::wstring name;
    public:
        OldVariableAccessExpression(std::wstring &name);
        std::wstring evaluate(SharedScope evalScope) override;
        void print(std::wstring tabsize=L"") override;
};