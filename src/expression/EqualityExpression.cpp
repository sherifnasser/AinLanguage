#include "EqualityExpression.hpp"
#include "BoolValue.hpp"
#include "Type.hpp"
#include <memory>

EqualityExpression::EqualityExpression(int lineNumber,SharedIExpression equalsFunEx)
:
    IExpression(lineNumber,Type::BOOL),
    equalsFunEx(equalsFunEx)
{}

std::vector<std::wstring> EqualityExpression::prettyPrint(){
    return equalsFunEx->prettyPrint();
}

bool EqualityExpression::evaluateEqualsFun(){
    auto equalsVal=equalsFunEx->evaluate();
    auto equalsBoolVal=std::dynamic_pointer_cast<BoolValue>(equalsVal)->getValue();
    return equalsBoolVal;
}

void EqualityExpression::check(SharedBaseScope checkScope){
    // The check of the return type of equals fun is done when parsing a function declaration
    equalsFunEx->check(checkScope);
}

SharedIValue EqualityExpression::EqualEqual::evaluate(){
    auto equals=evaluateEqualsFun();
    return std::make_shared<BoolValue>(equals);
}

SharedIValue EqualityExpression::NotEqual::evaluate(){
    auto equals=evaluateEqualsFun();
    return std::make_shared<BoolValue>(!equals);
}
