#pragma once
#include "SharedPtrTypes.hpp"
class IStatement{
    protected:
        SharedBaseScope runScope;
    public:
        IStatement(SharedBaseScope runScope);
        virtual void check()=0;
        virtual void run()=0;
};