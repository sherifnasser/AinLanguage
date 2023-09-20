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
        void accept(ASTVisitor *visitor) override;
        SharedIValue evaluate()override;
        SharedVector<SharedIExpression> getArgs() const;
        void setConstructor(SharedConstructorScope constructor);
};