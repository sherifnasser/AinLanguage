#pragma once
#include "IStatement.hpp"
#include "SharedPtrTypes.hpp"

class WhileStatement:public IStatement
{
    private:
        SharedIExpression condition;
        SharedStmListScope whileScope;

    public:
        WhileStatement(
            int lineNumber,
            SharedStmListScope runScope,
            SharedIExpression condition,
            SharedStmListScope whileScope
        );
        void check() override;
        void run() override;
};