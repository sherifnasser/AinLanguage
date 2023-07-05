#include "VarAccessExpression.hpp"
#include "Variable.hpp"

VarAccessExpression::VarAccessExpression(
    int lineNumber,
    std::wstring varName,
    SharedVariable var
):
IExpression(lineNumber,(var)?var->getType():nullptr),
varName(varName),
var(var)
{}
