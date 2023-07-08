#include "UnitExpression.hpp"
#include <string>

UnitExpression::UnitExpression(int lineNumber):
IExpression(lineNumber,Type::UNIT){}

std::vector<std::wstring> UnitExpression::prettyPrint() {
    return {L"UnitExpression at "+std::to_wstring(lineNumber)};
}

SharedIValue UnitExpression::evaluate() {
    
}

void UnitExpression::check(SharedBaseScope checkScope) {
    
}
