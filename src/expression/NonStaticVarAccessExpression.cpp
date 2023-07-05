#include "NonStaticVarAccessExpression.hpp"
NonStaticVarAccessExpression::NonStaticVarAccessExpression(
    int lineNumber,
    std::wstring varName,
    SharedIExpression inside
):
    IExpression(lineNumber,nullptr),
    varName(varName),
    inside(inside){}
