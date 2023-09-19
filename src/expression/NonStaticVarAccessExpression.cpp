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

SharedIValue NonStaticVarAccessExpression::evaluate(){
    auto propertyVal=inside->evaluateAs<ObjectValue>()->findPropertyValue(varName);
    return propertyVal;
}

void NonStaticVarAccessExpression::check(SharedBaseScope checkScope){
    inside->check(checkScope);
    auto insideType=inside->getReturnType();
    auto insideClassScope=insideType->getClassScope();

    auto publicVar=insideClassScope->findPublicVariable(varName);

    if(publicVar){
        this->returnType=publicVar->getType();
        checkType();
        return;
    }

    auto privateVar=insideClassScope->findPrivateVariable(varName);

    // TODO: make trace more readable
    auto trace=
        BaseScope::getContainingFile(checkScope)->getName()+
        L"::"+checkScope->getName()+L"("+std::to_wstring(lineNumber)+L")";

    if(!privateVar)
        throw VariableNotFoundException(trace,insideClassScope->getName()+L"::"+varName);
    
    if(insideClassScope!=BaseScope::getContainingClass(checkScope))
        throw CannotAccessPrivateVariableException(trace,varName);

    this->returnType=privateVar->getType();
    checkType();
}

void NonStaticVarAccessExpression::checkType(){
	if(!this->returnType){
		throw MustHaveExplicitTypeException(lineNumber);
	}
}

std::wstring NonStaticVarAccessExpression::getVarName()const{
    return varName;
}

SharedIExpression NonStaticVarAccessExpression::getInside()const{
    return inside;
}