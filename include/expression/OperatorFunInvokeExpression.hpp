#pragma once
#include "NonStaticFunInvokeExpression.hpp"
#include "SharedPtrTypes.hpp"
class OperatorFunInvokeExpression:public NonStaticFunInvokeExpression{
    private:
        SharedLexerToken op;
    public:
        OperatorFunInvokeExpression(
            int lineNumber,
            SharedLexerToken op,
            SharedVector<SharedIExpression> args,
            SharedIExpression inside
        );
};