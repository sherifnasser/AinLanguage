#pragma once
#include "IExpression.hpp"
#include "Type.hpp"
class UnitExpression:public IExpression{
    public:
        UnitExpression(int lineNumber):
        IExpression(lineNumber,Type::UNIT){}
};