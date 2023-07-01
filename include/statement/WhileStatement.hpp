#pragma once
#include "IOldStatement.hpp"

class WhileStatement:public IOldStatement
{
    protected:
        SharedIOldExpression ex;
        SharedVector<SharedIOldStatement> stmList;

    public:
        WhileStatement(
            SharedOldFunScope runScope,
            SharedIOldExpression ex,
            SharedVector<SharedIOldStatement> stmList
        );
        void run() override;
};