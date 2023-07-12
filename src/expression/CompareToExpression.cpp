#include "CompareToExpression.hpp"
#include "BoolValue.hpp"
#include "IntValue.hpp"
#include "Type.hpp"
#include <memory>

CompareToExpression::CompareToExpression(
    int lineNumber,
    SharedIExpression compareToFunEx,
    EVALUATION_FUN evaluationFun
):
    IExpression(lineNumber,Type::BOOL),
    compareToFunEx(compareToFunEx),
    evaluationFun(

        (evaluationFun==EVALUATION_FUN::GREATER)
        ?[](int compareToResult){
            return std::make_shared<BoolValue>(compareToResult>0);
        }:

        (evaluationFun==EVALUATION_FUN::GREATER_EQUAL)
        ?[](int compareToResult){
            return std::make_shared<BoolValue>(compareToResult>=0);
        }:

        (evaluationFun==EVALUATION_FUN::LESS)
        ?[](int compareToResult){
            return std::make_shared<BoolValue>(compareToResult<0);
        }:
        
        [](int compareToResult){
            return std::make_shared<BoolValue>(compareToResult<=0);
        }
    )
{}

std::vector<std::wstring> CompareToExpression::prettyPrint() {
    return compareToFunEx->prettyPrint();
}

SharedIValue CompareToExpression::evaluate(){
    auto compareToVal=compareToFunEx->evaluate();
    auto compareToIntVal=std::dynamic_pointer_cast<IntValue>(compareToVal)->getValue();
    return evaluationFun(compareToIntVal);
}

void CompareToExpression::check(SharedBaseScope checkScope){
    // The check of the return type of compareTo fun is done when parsing a function declaration
    compareToFunEx->check(checkScope);
}
