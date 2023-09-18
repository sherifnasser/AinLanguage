#pragma once
#include "IExpression.hpp"
#include "SharedPtrTypes.hpp"
#include <string>
class NewObjectExpression:public IExpression{
    private:
        SharedVector<SharedIExpression> args;
        SharedConstructorScope constructor;
    public:
        NewObjectExpression(int lineNumber,SharedType type, SharedVector<SharedIExpression> args);
        std::vector<std::wstring> prettyPrint()override;
        SharedIValue evaluate()override;
        void check(SharedBaseScope checkScope)override;
};