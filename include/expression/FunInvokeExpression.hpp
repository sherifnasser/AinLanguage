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
        FunInvokeExpression(int lineNumber,std::wstring funName,SharedVector<SharedIExpression> args);
        void accept(ASTVisitor *visitor) override;
        std::vector<std::wstring> prettyPrint()override;
        SharedIValue evaluate()override;
        void check(SharedBaseScope checkScope)override;
};