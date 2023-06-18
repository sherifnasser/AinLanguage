#pragma once
#include"Scope.hpp"

class Variable
{
protected:
    SharedScope parentScope;
    std::wstring name;
    std::wstring type;
    std::wstring currentVal;
    bool isInitialized=false;

    public:
        Variable(SharedScope parentScope, std::wstring &name, std::wstring &type);
        std::wstring getName();
        std::wstring getType();
        std::wstring getCurrentValue();
        virtual void setCurrentValue(std::wstring value);
};