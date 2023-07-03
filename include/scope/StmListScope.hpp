#pragma once
#include "BaseScope.hpp"

class StmListScope:public BaseScope{

    protected:
        SharedMap<std::wstring, SharedVariable> locals;
        SharedStmList stmList;
        StmListScope(std::wstring name,SharedBaseScope parentScope);

    public:
        SharedMap<std::wstring, SharedVariable> getLocals();
};