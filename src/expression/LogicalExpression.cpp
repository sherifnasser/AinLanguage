#include "LogicalExpression.hpp"
#include "BoolValue.hpp"
#include "Type.hpp"
#include <memory>
#include <string>
#include <vector>

LogicalExpression::LogicalExpression(
    int lineNumber,
    SharedIExpression left,
    SharedIExpression right
)
    : IExpression(lineNumber,Type::BOOL),
      left(left),
      right(right){}

bool LogicalExpression::evaluateLeft(){
    auto leftVal=std::dynamic_pointer_cast<BoolValue>(left->evaluate())->getValue();
    return leftVal;
}

std::shared_ptr<BoolValue> LogicalExpression::evaluateRight(){
    auto rightVal=std::dynamic_pointer_cast<BoolValue>(right->evaluate())->getValue();
    return std::make_shared<BoolValue>(rightVal);
}

void LogicalExpression::check(SharedBaseScope checkScope){
    left->check(checkScope);
    right->check(checkScope);

    if(left->getReturnType()->getClassScope()!=Type::BOOL->getClassScope())
        throw;
    
    if(right->getReturnType()->getClassScope()!=Type::BOOL->getClassScope())
        throw;
}

std::vector<std::wstring> LogicalExpression::prettyPrint(){
    auto prints=std::vector<std::wstring>();

    prints.push_back(L"LogicalExpression");

    auto leftPrints=left->prettyPrint();

    leftPrints[0]=L"├──"+leftPrints[0];
    for(int j=1;j<leftPrints.size();j++){
        leftPrints[j]=L"│   "+leftPrints[j];
    }
    prints.insert(prints.end(),leftPrints.begin(),leftPrints.end());
    
    auto rightPrints=right->prettyPrint();
    rightPrints[0]=L"└──"+rightPrints[0];
    for(int j=1;j<rightPrints.size();j++){
        rightPrints[j]=L"    "+rightPrints[j];
    }

    prints.insert(prints.end(),rightPrints.begin(),rightPrints.end());

    return prints;
}

std::vector<std::wstring> LogicalExpression::Or::prettyPrint(){
    auto prints=LogicalExpression::prettyPrint();

    auto lineNumStr=std::to_wstring(lineNumber);
    
    prints[0]=L"LogicalExpression \'||\' at "+lineNumStr;

    return prints;
}

SharedIValue LogicalExpression::Or::evaluate(){
    if(evaluateLeft())
        return std::make_shared<BoolValue>(true);
    
    return evaluateRight();
}

std::vector<std::wstring> LogicalExpression::And::prettyPrint() {
    auto prints=LogicalExpression::prettyPrint();

    auto lineNumStr=std::to_wstring(lineNumber);
    
    prints[0]=L"LogicalExpression \'&&\' at "+lineNumStr;

    return prints;
}

SharedIValue LogicalExpression::And::evaluate(){
    if(!evaluateLeft())
        return std::make_shared<BoolValue>(false);
    
    return evaluateRight();
}
