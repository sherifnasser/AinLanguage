#pragma once
#include"Variable.hpp"

class Constant:public Variable
{
    public:
        Constant(SharedScope parentScope, std::wstring &name, std::wstring &type);
        void setCurrentValue(std::wstring value) override;
};