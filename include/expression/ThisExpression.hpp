#pragma once
#include "IExpression.hpp"
#include "SharedPtrTypes.hpp"
#include <string>
class ThisExpression:public IExpression{
    public:
        ThisExpression(int lineNumber);
        void accept(ASTVisitor *visitor) override;
};