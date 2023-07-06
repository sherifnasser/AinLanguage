#include "VarAccessExpression.hpp"
#include "Variable.hpp"
#include <string>

VarAccessExpression::VarAccessExpression(
    int lineNumber,
    std::wstring varName,
    SharedVariable var
):
IExpression(lineNumber,(var)?var->getType():nullptr),
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
    
}

void VarAccessExpression::check(SharedBaseScope checkScope) {
    
}
