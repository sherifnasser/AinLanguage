#pragma once
#include "scope.hpp"

class globalscope:public scope
{
    public:
        globalscope();
        void addfunction(funscope* funscope);
        funscope* getmain();
};