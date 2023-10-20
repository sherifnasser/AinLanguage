#include "NonStaticVarAccessExpression.hpp"
#include "CannotAccessPrivateVariableException.hpp"
#include "IExpression.hpp"
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

SharedVariable NonStaticVarAccessExpression::getVar()const{
    return var;
}

void NonStaticVarAccessExpression::setVar(SharedVariable var){
    this->var=var;
}