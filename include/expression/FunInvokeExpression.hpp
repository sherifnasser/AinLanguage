#pragma once
#include "IExpression.hpp"
#include "SharedPtrTypes.hpp"
#include <string>
class FunInvokeExpression:public IExpression{
    private:
        SharedFunScope fun;
        std::wstring funName;
        SharedVector<SharedIExpression> args;
    public:
        FunInvokeExpression(int lineNumber,std::wstring funName, SharedVector<SharedIExpression> args);
        void check(SharedBaseScope checkScope)override;
};