#pragma once
#include "SharedPtrTypes.hpp"
class IStatement{
    protected:
        int lineNumber;
        SharedStmListScope runScope;
    public:
        IStatement(int lineNumber,SharedStmListScope runScope);
        virtual void check()=0;
        virtual void run()=0;
};