#pragma once
#include "IExpression.hpp"
#include "Type.hpp"
class UnitExpression:public IExpression{
    public:
        UnitExpression(int lineNumber);
        std::vector<std::wstring> prettyPrint() override;
        SharedIValue evaluate() override;
        void check(SharedBaseScope checkScope) override;
};