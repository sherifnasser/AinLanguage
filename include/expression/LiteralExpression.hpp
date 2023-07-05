#pragma once
#include "IExpression.hpp"
#include "SharedPtrTypes.hpp"
class LiteralExpression:public IExpression{
    private:
        SharedIValue value;
    public:
        LiteralExpression(int lineNumber,SharedIValue value);
};