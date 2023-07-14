#include "IExpression.hpp"

IExpression::IExpression(int lineNumber,SharedType returnType)
:lineNumber(lineNumber),returnType(returnType){}

SharedType IExpression::getReturnType() {
    return this->returnType;
}

IExpression::~IExpression(){}
