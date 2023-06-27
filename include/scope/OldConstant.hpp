#pragma once
#include"OldVariable.hpp"

class OldConstant:public OldVariable
{
    public:
        OldConstant(SharedScope parentScope, std::wstring &name, std::wstring &type);
        void setCurrentValue(std::wstring value) override;
};