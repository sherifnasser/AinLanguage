#pragma once
#include "ASTNode.hpp"
#include "SharedPtrTypes.hpp"
class IStatement:public ASTNode{
    protected:
        int lineNumber;
        SharedBaseScope runScope;
    public:
        IStatement(int lineNumber,SharedBaseScope runScope);
        virtual void check()=0;
        virtual void run()=0;
};