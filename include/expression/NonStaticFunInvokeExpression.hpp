#pragma once
#include "IExpression.hpp"
#include "SharedPtrTypes.hpp"
#include <string>
class NonStaticFunInvokeExpression:public IExpression{
    protected:
        std::wstring funName;
        SharedFunScope fun;
        SharedIExpression inside;
        SharedVector<SharedIExpression> args;
    public:
        NonStaticFunInvokeExpression(
            int lineNumber,
            std::wstring funName,
            SharedVector<SharedIExpression> args,
            SharedIExpression inside
        );
        void accept(ASTVisitor *visitor) override;
        SharedIValue evaluate()override;
        void check(SharedBaseScope checkScope)override;
        virtual ~NonStaticFunInvokeExpression();

        std::wstring getFunName() const;

        SharedIExpression getInside() const;

        SharedVector<SharedIExpression> getArgs() const;
};