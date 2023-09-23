#pragma once
#include "IExpression.hpp"
#include "IStatement.hpp"
#include "SharedPtrTypes.hpp"
#include <memory>

class AssignStatement:public IStatement{
    public:
        AssignStatement(
            int lineNumber,
            SharedStmListScope runScope,
            SharedIExpression ex,
            SharedIExpression newValEx,
            bool isAugmented
        );

        void accept(ASTVisitor *visitor) override;

        SharedIExpression getEx()const;

        SharedIExpression getNewValEx()const;

        bool isAugmentedAssignment()const;
    
    private:
        bool isAugmented;
        SharedIExpression ex;
        SharedIExpression newValEx;
};