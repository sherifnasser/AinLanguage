#pragma once
#include "IExpression.hpp"
#include "SharedPtrTypes.hpp"
#include <string>
class NonStaticFunInvokeExpression:public IExpression{
    private:
        std::wstring funName;
        SharedVector<SharedIExpression> args;
        SharedIExpression inside;
    public:
        NonStaticFunInvokeExpression(
            int lineNumber,
            std::wstring funName,
            SharedVector<SharedIExpression> args,
            SharedIExpression inside
        );
};