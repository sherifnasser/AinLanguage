#pragma once
#include "IStatement.hpp"
#include "SharedPtrTypes.hpp"

class IfStatement:public IStatement
{
    private:
        SharedIExpression ifCondition;
        SharedStmListScope ifScope;
        SharedStmListScope elseScope;

    public:
        IfStatement(
            int lineNumber,
            SharedStmListScope runScope,
            SharedIExpression ifCondition,
            SharedStmListScope ifScope,
            SharedStmListScope elseScope
        );
        void check() override;
        void run() override;
};