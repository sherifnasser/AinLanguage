#include "IExpression.hpp"
#include "VarAccessExpression.hpp"
#include "NonStaticVarAccessExpression.hpp"

IExpression::IExpression(int lineNumber,SharedType returnType)
:lineNumber(lineNumber),returnType(returnType){}

SharedType IExpression::getReturnType() {
    return this->returnType;
}

void IExpression::setReturnType(SharedType returnType){
    this->returnType=returnType;
}

IExpression::~IExpression(){}
int IExpression::getLineNumber()const{
    return lineNumber;
}

bool IExpression::isAssignableExpression(SharedIExpression ex){
    return
        std::dynamic_pointer_cast<VarAccessExpression>(ex)!=nullptr
        ||
        std::dynamic_pointer_cast<NonStaticVarAccessExpression>(ex)!=nullptr
    ;
}
