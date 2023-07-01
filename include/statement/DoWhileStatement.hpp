#pragma once
#include "WhileStatement.hpp"

class DoWhileStatement:public WhileStatement
{
    public:
        DoWhileStatement(
            SharedOldFunScope runScope,
            SharedIOldExpression ex,
            SharedVector<SharedIOldStatement> stmList
        );
        void run() override;
};