#include "OperatorFunInvokeExpression.hpp"
#include "LexerToken.hpp"

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
