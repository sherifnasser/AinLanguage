#include "NonStaticVarAccessExpression.hpp"
#include "CannotAccessPrivateVariableException.hpp"
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
    AssignStatement::AssignExpression(lineNumber,nullptr),
    varName(varName),
    inside(inside){}

std::vector<std::wstring> NonStaticVarAccessExpression::prettyPrint(){

    auto prints=std::vector<std::wstring>();
    auto lineNumStr=std::to_wstring(lineNumber);
    prints.push_back(L"NonStaticVarAccessExpression \'"+varName+L"\' at "+lineNumStr);

    auto insidePrints=inside->prettyPrint();
    
    insidePrints[0]=L"└──\033[1;33m"+insidePrints[0]+L"\033[0m";

    for(int i=1;i<insidePrints.size();i++){   
        insidePrints[i]=L"    "+insidePrints[i];
    }

    prints.insert(prints.end(),insidePrints.begin(),insidePrints.end());

    return prints;
}

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

void NonStaticVarAccessExpression::assign(SharedIValue newVal){
    inside->evaluateAs<ObjectValue>()->assignProperty(varName,newVal);
}