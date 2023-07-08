#pragma once
#include "IExpression.hpp"
#include "SharedPtrTypes.hpp"
class LiteralExpression:public IExpression{
    private:
        SharedIValue value;
    public:
        LiteralExpression(int lineNumber,SharedIValue value);
        std::vector<std::wstring> prettyPrint()override;
        SharedIValue evaluate()override;
        void check(SharedBaseScope checkScope)override;
};