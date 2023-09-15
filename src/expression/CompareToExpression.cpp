#include "CompareToExpression.hpp"
#include "BoolValue.hpp"
#include "IntValue.hpp"
#include "Type.hpp"
#include <memory>

CompareToExpression::CompareToExpression(int lineNumber,SharedIExpression compareToFunEx)
    : IExpression(lineNumber,Type::BOOL),
      compareToFunEx(compareToFunEx){}

std::vector<std::wstring> CompareToExpression::prettyPrint(){
    return compareToFunEx->prettyPrint();
}

int CompareToExpression::evaluateCompareToFun(){
    auto compareToVal=compareToFunEx->evaluateAs<IntValue>()->getValue();
    return compareToVal;
}

void CompareToExpression::check(SharedBaseScope checkScope){
    // The check of the return type of compareTo fun is done when parsing a function declaration
    compareToFunEx->check(checkScope);
}

SharedIValue CompareToExpression::Less::evaluate(){
    auto compareToVal=evaluateCompareToFun();
    return std::make_shared<BoolValue>(compareToVal<0);
}

SharedIValue CompareToExpression::LessEqual::evaluate(){
    auto compareToVal=evaluateCompareToFun();
    return std::make_shared<BoolValue>(compareToVal<=0);
}

SharedIValue CompareToExpression::Greater::evaluate(){
    auto compareToVal=evaluateCompareToFun();
    return std::make_shared<BoolValue>(compareToVal>0);
}

SharedIValue CompareToExpression::GreaterEqual::evaluate(){
    auto compareToVal=evaluateCompareToFun();
    return std::make_shared<BoolValue>(compareToVal>=0);
}
