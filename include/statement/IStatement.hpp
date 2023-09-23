#pragma once
#include "ASTNode.hpp"
#include "SharedPtrTypes.hpp"
class IStatement:public ASTNode{
    protected:
        int lineNumber;
        SharedBaseScope runScope;
    public:
        IStatement(int lineNumber,SharedBaseScope runScope);

        int getLineNumber()const;

        SharedBaseScope getRunScope()const;
};