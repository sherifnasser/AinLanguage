#pragma once
#include "WhileStatement.hpp"

class DoWhileStatement:public WhileStatement
{
    public:
        DoWhileStatement(
            SharedFunScope runScope,
            SharedIExpression ex,
            SharedVector<SharedIStatement> stmList
        );
        void run() override;
};