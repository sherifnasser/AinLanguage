#pragma once
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

        SharedVariable getVar() const;
        void check() override;
        void run() override;
};