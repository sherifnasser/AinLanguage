#pragma once
#include "Scope.hpp"

class GlobalScope:public Scope
{
    public:
        GlobalScope();
        void addfunction(SharedFunScope funScope);
        SharedFunScope getMain();
};