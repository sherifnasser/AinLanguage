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