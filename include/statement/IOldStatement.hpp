#pragma once
#include "Scope.hpp"

class IOldStatement
{
    protected:
        SharedScope runScope;
    public:
        IOldStatement(SharedScope runScope);
        virtual void run()=0;
};