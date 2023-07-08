#include "VarAccessExpression.hpp"
#include "Variable.hpp"
#include <string>

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

SharedIValue VarAccessExpression::evaluate() {
    return var->getValue();
}

void VarAccessExpression::check(SharedBaseScope checkScope) {
    if(var){
        this->returnType=var->getType();
        return;
    }
    
    // TODO: non-local variables
}

void VarAccessExpression::assign(SharedIValue newVal) {
    var->setValue(newVal);
}
