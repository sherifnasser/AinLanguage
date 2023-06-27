#pragma once
#include "IStatement.hpp"

class VarDeclarationStatement:public IStatement
{
    private:
        SharedOldVariable var;
        SharedIExpression ex;
    public:
        VarDeclarationStatement(SharedScope runScope,SharedOldVariable var,SharedIExpression ex);
        void run() override;
};