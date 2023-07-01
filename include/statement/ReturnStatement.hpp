#pragma once
#include "IOldStatement.hpp"

class ReturnStatement:public IOldStatement
{
    private:
        SharedIOldExpression ex;
    public:
        ReturnStatement(SharedOldFunScope runScope,SharedIOldExpression ex);
        void run() override;
};