#include "VarAccessExpression.hpp"
#include "BaseScope.hpp"
#include "ClassScope.hpp"
#include "FileScope.hpp"
#include "PackageScope.hpp"
#include "VariableNotFoundException.hpp"
#include "MustHaveExplicitTypeException.hpp"
#include "Variable.hpp"
#include <string>

void VarAccessExpression::setVar(SharedVariable var){
    this->var=var;
    this->returnType=var->getType();
    checkType();
}

VarAccessExpression::VarAccessExpression(
    int lineNumber,
    std::wstring varName,
    SharedVariable var
):
AssignStatement::AssignExpression(lineNumber,(var)?var->getType():nullptr),
varName(varName),
var(var)
{}

SharedIValue VarAccessExpression::evaluate(){
    return var->getValue();
}

void VarAccessExpression::check(SharedBaseScope checkScope){
    if(var){
        this->returnType=var->getType();
        checkType();
        return;
    }

    auto containingClassScope=BaseScope::getContainingClass(checkScope);
    if(containingClassScope){
        
        auto publicVar=containingClassScope->findPublicVariable(varName);

        if(publicVar){
            setVar(publicVar);
            return;
        }

        auto privateVar=containingClassScope->findPrivateVariable(varName);

        if(privateVar){
            setVar(privateVar);
            return;
        }
    }

    auto containingFileScope=BaseScope::getContainingFile(checkScope);
    if(containingFileScope){

        auto privateVar=containingFileScope->findPrivateVariable(varName);

        if(privateVar){
            setVar(privateVar);
            return;
        }

        auto package=BaseScope::toPackageScope(containingFileScope->getParentScope());
        
        for(auto file:package->getFiles()){
            auto publicVar=file.second->findPublicVariable(varName);
            if(publicVar){
                setVar(publicVar);
                return;
            }
        }
        
        // TODO: make trace more readable
        auto trace=
            containingFileScope->getName()+
            L"::"+checkScope->getName()+L"("+std::to_wstring(lineNumber)+L")";
        
        throw VariableNotFoundException(trace,varName);
    }
    
}

void VarAccessExpression::checkType(){
	if(!this->returnType){
		throw MustHaveExplicitTypeException(lineNumber);
	}
}

void VarAccessExpression::assign(SharedIValue newVal){
    var->setValue(newVal);
}

SharedVariable VarAccessExpression::getVar()const{
    return var;
}

std::wstring VarAccessExpression::getVarName()const{
    return varName;
}