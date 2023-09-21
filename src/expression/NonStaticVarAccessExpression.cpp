#include "NonStaticVarAccessExpression.hpp"
#include "CannotAccessPrivateVariableException.hpp"
#include "IExpression.hpp"
#include "ObjectValue.hpp"
#include "Type.hpp"
#include "ClassScope.hpp"
#include "Variable.hpp"
#include "FileScope.hpp"
#include "VariableNotFoundException.hpp"
#include "MustHaveExplicitTypeException.hpp"

NonStaticVarAccessExpression::NonStaticVarAccessExpression(
    int lineNumber,
    std::wstring varName,
    SharedIExpression inside
):
    IExpression(lineNumber,nullptr),
    varName(varName),
    inside(inside){}

std::wstring NonStaticVarAccessExpression::getVarName()const{
    return varName;
}

SharedIExpression NonStaticVarAccessExpression::getInside()const{
    return inside;
}