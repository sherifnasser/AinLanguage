#pragma once
#include "ASTNode.hpp"
#include "IStatement.hpp"
#include "SharedPtrTypes.hpp"
class VarStm:public IStatement{
    private:
        SharedVariable var;
        SharedIExpression ex;
    public:

        VarStm(
            int lineNumber,
            SharedBaseScope runScope,
            SharedVariable var,
            SharedIExpression ex
        );

        void accept(ASTVisitor *visitor)override;

        SharedVariable getVar()const;
        void run() override;

        SharedIExpression getEx()const;
};