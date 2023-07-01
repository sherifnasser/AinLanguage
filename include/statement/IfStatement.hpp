#pragma once
#include "IOldStatement.hpp"

class IfStatement:public IOldStatement
{
    private:
        SharedIOldExpression ifCondition;
        SharedVector<SharedIOldStatement> ifStmList;
        SharedVector<SharedIOldStatement> elseStmList;
    public:
        IfStatement(
            SharedOldFunScope runScope,
            SharedIOldExpression ifCondition,
            SharedVector<SharedIOldStatement> ifStmList,
            SharedVector<SharedIOldStatement> elseStmList
        );
        void run() override;
};