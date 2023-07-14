#pragma once
#include "IStatement.hpp"
#include "SharedPtrTypes.hpp"

class DoWhileStatement:public IStatement
{
    private:
        SharedIExpression condition;
        SharedStmListScope doWhileScope;
    
    public:
        DoWhileStatement(
            int lineNumber,
            SharedStmListScope runScope,
            SharedIExpression condition,
            SharedStmListScope doWhileScope
        );
        void check() override;
        void run() override;
};