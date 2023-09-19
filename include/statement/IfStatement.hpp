#pragma once
#include "IStatement.hpp"
#include "SharedPtrTypes.hpp"

class IfStatement:public IStatement
{
    private:
        SharedIExpression ifCondition;
        SharedStmListScope ifScope;
        SharedStmListScope elseScope;
        SharedFunScope containingFunScope;

    public:
        IfStatement(
            int lineNumber,
            SharedStmListScope runScope,
            SharedIExpression ifCondition,
            SharedStmListScope ifScope,
            SharedStmListScope elseScope
        );

        void accept(ASTVisitor *visitor) override;
        void run() override;

        SharedIExpression getIfCondition()const;

        SharedStmListScope getIfScope()const;

        SharedStmListScope getElseScope()const;

        SharedFunScope getContainingFunScope()const;
};