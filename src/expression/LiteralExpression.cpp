#include "LiteralExpression.hpp"
#include "IValue.hpp"
#include <iostream>
#include <string>
#include <vector>
LiteralExpression::LiteralExpression(int lineNumber,SharedIValue value)
    : IExpression(lineNumber,value->getType()),
      value(value){}

std::vector<std::wstring> LiteralExpression::prettyPrint(){
    return{
        L"LiteralExpression \'"+value->toString()+
        L"\' at "+std::to_wstring(lineNumber)
    };
}

SharedIValue LiteralExpression::evaluate() {
    return this->value;
}

void LiteralExpression::check(SharedBaseScope checkScope) {
    
}
