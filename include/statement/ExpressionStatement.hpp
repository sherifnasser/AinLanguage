#pragma once
#include "IOldStatement.hpp"

class ExpressionStatement:public IOldStatement
{
    private:
        SharedIOldExpression ex;
    public:
        ExpressionStatement(SharedScope runScope,SharedIOldExpression ex);
        void run() override;
};