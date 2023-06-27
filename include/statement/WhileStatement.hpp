#pragma once
#include "IStatement.hpp"

class WhileStatement:public IStatement
{
    protected:
        SharedIExpression ex;
        SharedVector<SharedIStatement> stmList;

    public:
        WhileStatement(
            SharedOldFunScope runScope,
            SharedIExpression ex,
            SharedVector<SharedIStatement> stmList
        );
        void run() override;
};