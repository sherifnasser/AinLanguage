#pragma once
#include "IStatement.hpp"

class VarDeclarationStatement:public IStatement
{
    private:
        SharedVariable var;
        SharedIExpression ex;
    public:
        VarDeclarationStatement(SharedScope runScope,SharedVariable var,SharedIExpression ex);
        void run() override;
};