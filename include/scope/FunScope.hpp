#pragma once
#include "SharedPtrTypes.hpp"
#include "StmListScope.hpp"
#include <map>
#include <string>

class FunScope:public StmListScope{
    private:
        SharedFunDecl decl;
        SharedClassScope returnType;
        // TODO add params for shadowing
        // SharedMap<std::wstring, SharedVariable> params;
    public:
        FunScope(
            SharedBaseScope parentScope,
            SharedFunDecl decl
        );
        void check();
        SharedIValue invoke(std::map<std::wstring, SharedIValue> params);
        SharedClassScope getReturnType();
        void setReturnType(SharedClassScope returnType);
};