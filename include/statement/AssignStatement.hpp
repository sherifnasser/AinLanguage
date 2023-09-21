#pragma once
#include "IExpression.hpp"
#include "IStatement.hpp"
#include "SharedPtrTypes.hpp"
#include <memory>

class AssignStatement:public IStatement{
    public:
        AssignStatement(
            int lineNumber,
            SharedStmListScope runScope,
            SharedIExpression ex,
            SharedIExpression newValEx
        );

        void accept(ASTVisitor *visitor) override;

        SharedIExpression getEx()const;

        SharedIExpression getNewValEx()const;
    
    private:
        SharedIExpression ex;
        SharedIExpression newValEx;
};