#pragma once
#include "SharedPtrTypes.hpp"
class IStatement{
    protected:
        int lineNumber;
        SharedBaseScope runScope;
    public:
        IStatement(int lineNumber,SharedBaseScope runScope);
        virtual void check()=0;
        virtual void run()=0;
};