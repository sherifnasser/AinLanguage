#include "LogicalExpression.hpp"
#include "BoolValue.hpp"
#include "Type.hpp"
#include "UnexpectedTypeException.hpp"
#include <memory>
#include <string>
#include <vector>

LogicalExpression::LogicalExpression(
    int lineNumber,
    Operation logicalOp,
    SharedIExpression left,
    SharedIExpression right
)
    : IExpression(lineNumber,Type::BOOL),
    logicalOp(logicalOp),
    left(left),
    right(right){}

bool LogicalExpression::evaluateLeft(){
    auto leftVal=left->evaluateAs<BoolValue>()->getValue();
    return leftVal;
}

std::shared_ptr<BoolValue> LogicalExpression::evaluateRight(){
    auto rightVal=right->evaluateAs<BoolValue>()->getValue();
    return std::make_shared<BoolValue>(rightVal);
}

void LogicalExpression::check(SharedBaseScope checkScope){
    left->check(checkScope);
    right->check(checkScope);

    if(left->getReturnType()->getClassScope()!=Type::BOOL->getClassScope())
        throw UnexpectedTypeException(
            lineNumber,
            *Type::BOOL_NAME,
            *left->getReturnType()->getName()
        );
    
    if(right->getReturnType()->getClassScope()!=Type::BOOL->getClassScope())
        throw UnexpectedTypeException(
            lineNumber,
            *Type::BOOL_NAME,
            *right->getReturnType()->getName()
        );
}

SharedIValue LogicalExpression::evaluate(){
    return nullptr;
}

SharedIExpression LogicalExpression::getLeft()const{
    return left;
}

SharedIExpression LogicalExpression::getRight()const{
    return right;
}

LogicalExpression::Operation LogicalExpression::getLogicalOp()const{
    return logicalOp;
}