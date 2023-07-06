#include "OperatorFunInvokeExpression.hpp"
#include "LexerToken.hpp"
#include "NonStaticFunInvokeExpression.hpp"

OperatorFunInvokeExpression::OperatorFunInvokeExpression(
    int lineNumber,
    SharedLexerToken op,
    SharedVector<SharedIExpression> args,
    SharedIExpression inside
):
NonStaticFunInvokeExpression(
    lineNumber,
    op->getVal(),
    args,
    inside
),
op(op){}

std::vector<std::wstring> OperatorFunInvokeExpression::prettyPrint(){

    auto superPrints=NonStaticFunInvokeExpression::prettyPrint();

    auto lineNumStr=std::to_wstring(lineNumber);

    superPrints[0]=L"\033[36;1mOperatorFunInvokeExpression \'"+funName+L"\' at "+lineNumStr+L"\033[0m";

    return superPrints;
}

SharedIValue OperatorFunInvokeExpression::evaluate(){
    
}

void OperatorFunInvokeExpression::check(SharedBaseScope checkScope) {
    
}
