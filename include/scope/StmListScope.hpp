#pragma once
#include "BaseScope.hpp"
#include "SharedPtrTypes.hpp"
#include <string>

class StmListScope:public BaseScope{

    protected:
        SharedMap<std::wstring, SharedVariable> locals;
        SharedStmList stmList;
        StmListScope(std::wstring name,SharedBaseScope parentScope);

    public:
        SharedMap<std::wstring, SharedVariable> getLocals();
        SharedStmList getStmList();
        SharedVariable getVarByName(std::wstring varName)override;
        SharedVariable getLocalByName(std::wstring varName);
};