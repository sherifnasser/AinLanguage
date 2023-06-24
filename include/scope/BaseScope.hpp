#pragma once
// TODO: change name
#include "SharedPtrTypes.hpp"
class BaseScope{
protected:
    SharedBaseScope parentScope;

    std::wstring name;
public:
    BaseScope(std::wstring name,SharedBaseScope parentScope);
    SharedBaseScope getParentScope();
    std::wstring getName();
    virtual ~BaseScope();
};