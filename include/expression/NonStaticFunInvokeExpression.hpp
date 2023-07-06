#pragma once
#include "IExpression.hpp"
#include "SharedPtrTypes.hpp"
#include <string>
class NonStaticFunInvokeExpression:public IExpression{
    protected:
        std::wstring funName;
    private:
        SharedVector<SharedIExpression> args;
        SharedIExpression inside;
    public:
        NonStaticFunInvokeExpression(
            int lineNumber,
            std::wstring funName,
            SharedVector<SharedIExpression> args,
            SharedIExpression inside
        );
        std::vector<std::wstring> prettyPrint()override;
        SharedIValue evaluate()override;
        void check(SharedBaseScope checkScope)override;
        virtual ~NonStaticFunInvokeExpression();
};