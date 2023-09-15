#pragma once
#include "IStatement.hpp"

class ExpressionStatement:public IStatement{
    
    private:
        SharedIExpression ex;
    public:
        ExpressionStatement(
            int lineNumber,
            SharedStmListScope runScope,
            SharedIExpression ex
        );
        void check() override;
        void run() override;
    
};