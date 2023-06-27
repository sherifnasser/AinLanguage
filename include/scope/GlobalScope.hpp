#pragma once
#include "Scope.hpp"

class GlobalScope:public Scope
{
    public:
        GlobalScope();
        void addfunction(SharedOldFunScope funScope);
        SharedOldFunScope getMain();
};