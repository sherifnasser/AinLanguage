#pragma once
#include "IStatement.hpp"

class IfStatement:public IStatement
{
    private:
        SharedIExpression ifCondition;
        SharedVector<SharedIStatement> ifStmList;
        SharedVector<SharedIStatement> elseStmList;
    public:
        IfStatement(
            SharedOldFunScope runScope,
            SharedIExpression ifCondition,
            SharedVector<SharedIStatement> ifStmList,
            SharedVector<SharedIStatement> elseStmList
        );
        void run() override;
};