#include "LiteralExpression.hpp"
#include "IValue.hpp"
LiteralExpression::LiteralExpression(int lineNumber,SharedIValue value)
    : IExpression(lineNumber,value->getType()),
      value(value){}