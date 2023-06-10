#pragma once
#include "Scope.hpp"

class IStatement
{
    protected:
        SharedScope runScope;
    public:
        IStatement(SharedScope runScope);
        virtual void run()=0;
};