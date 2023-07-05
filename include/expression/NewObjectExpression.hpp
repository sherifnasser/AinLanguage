#pragma once
#include "IExpression.hpp"
#include "SharedPtrTypes.hpp"
#include <string>
class NewObjectExpression:public IExpression{
    private:
        SharedVector<SharedIExpression> args;
    public:
        NewObjectExpression(int lineNumber,SharedType type, SharedVector<SharedIExpression> args);
        void check(SharedBaseScope checkScope)override;
};