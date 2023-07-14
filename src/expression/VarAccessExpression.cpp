#include "VarAccessExpression.hpp"
#include "BaseScope.hpp"
#include "ClassScope.hpp"
#include "FileScope.hpp"
#include "PackageScope.hpp"
#include "VariableNotFoundException.hpp"
#include "Variable.hpp"
#include <string>

void VarAccessExpression::setVar(SharedVariable var){
    this->var=var;
    this->returnType=var->getType();
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

std::vector<std::wstring> VarAccessExpression::prettyPrint(){
    return{
        L"VarAccessExpression \'"+varName+
        L"\' at "+std::to_wstring(lineNumber)
    };
}

SharedIValue VarAccessExpression::evaluate(){
    return var->getValue();
}

void VarAccessExpression::check(SharedBaseScope checkScope){
    if(var){
        this->returnType=var->getType();
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

void VarAccessExpression::assign(SharedIValue newVal){
    var->setValue(newVal);
}
