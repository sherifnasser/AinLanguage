#pragma once
#include "IStatement.hpp"

class ExpressionStatement:public IStatement
{
    private:
        SharedIExpression ex;
    public:
        ExpressionStatement(SharedScope runScope,SharedIExpression ex);
        void run() override;
};