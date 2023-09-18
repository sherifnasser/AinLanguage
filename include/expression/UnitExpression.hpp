#pragma once
#include "IExpression.hpp"
#include "Type.hpp"
class UnitExpression:public IExpression{
    public:
        UnitExpression(int lineNumber);
        void accept(ASTVisitor *visitor) override;
        std::vector<std::wstring> prettyPrint() override;
        SharedIValue evaluate() override;
        void check(SharedBaseScope checkScope) override;
};