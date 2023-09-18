#include "UnitExpression.hpp"
#include "UnitValue.hpp"
#include <memory>
#include <string>

UnitExpression::UnitExpression(int lineNumber):
IExpression(lineNumber,Type::UNIT){}

std::vector<std::wstring> UnitExpression::prettyPrint() {
    return {L"UnitExpression at "+std::to_wstring(lineNumber)};
}

SharedIValue UnitExpression::evaluate() {
    return std::make_shared<UnitValue>();
}

void UnitExpression::check(SharedBaseScope checkScope){}