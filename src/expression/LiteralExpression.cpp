#include "LiteralExpression.hpp"
#include "IValue.hpp"
#include <iostream>
#include <string>
#include <vector>
LiteralExpression::LiteralExpression(int lineNumber,SharedIValue value)
    : IExpression(lineNumber,value->getType()),
      value(value){}

SharedIValue LiteralExpression::evaluate() {
    return this->value;
}

void LiteralExpression::check(SharedBaseScope checkScope){
    
}

SharedIValue LiteralExpression::getValue()const{
    return value;
}