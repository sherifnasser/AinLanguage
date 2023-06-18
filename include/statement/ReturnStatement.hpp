#pragma once
#include "IStatement.hpp"

class ReturnStatement:public IStatement
{
    private:
        SharedIExpression ex;
    public:
        ReturnStatement(SharedFunScope runScope,SharedIExpression ex);
        void run() override;
};