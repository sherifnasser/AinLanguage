#pragma once
#include "scope.hpp"

class globalscope:public scope
{
    public:
        void addfunction(funscope &funscope);
};