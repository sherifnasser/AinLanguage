#pragma once
#include "IOldStatement.hpp"

class VarDeclarationStatement:public IOldStatement
{
    private:
        SharedOldVariable var;
        SharedIOldExpression ex;
    public:
        VarDeclarationStatement(SharedScope runScope,SharedOldVariable var,SharedIOldExpression ex);
        void run() override;
};