#pragma once
#include "NonStaticFunInvokeExpression.hpp"
#include "SharedPtrTypes.hpp"
#include <string>
class OperatorFunInvokeExpression:public NonStaticFunInvokeExpression{
    public:
        OperatorFunInvokeExpression(
            int lineNumber,
            std::wstring opName,
            SharedVector<SharedIExpression> args,
            SharedIExpression inside
        );
        void accept(ASTVisitor *visitor) override;
        std::vector<std::wstring> prettyPrint()override;
        void check(SharedBaseScope checkScope)override;
};