#include "SetOperatorExpression.hpp"
#include "OperatorFunInvokeExpression.hpp"

SetOperatorExpression::SetOperatorExpression(
    Operator op,
    SharedOpFunInvokeExpression exOfGet,
    SharedIExpression valueEx
)
:IExpression(exOfGet->getLineNumber(),nullptr),
    exOfGet(exOfGet),
    valueEx(valueEx),
    op(op)
{}

SharedOpFunInvokeExpression SetOperatorExpression::getExOfGet()const{
    return this->exOfGet;
}

SharedIExpression SetOperatorExpression::getValueEx()const{
    return this->valueEx;
}

SharedFunScope SetOperatorExpression::getFun()const{
    return this->fun;
}

void SetOperatorExpression::setFun(SharedFunScope fun){
    this->fun=fun;
}