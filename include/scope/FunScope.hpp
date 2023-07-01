#pragma once
#include "BaseScope.hpp"
#include "SharedPtrTypes.hpp"
#include <map>
class FunScope:public BaseScope{
    private:
        SharedFunDecl decl;
        SharedClassScope returnType;
        std::map<SharedWString, SharedVariable> locals;
        SharedVector<SharedIStatement> stmList;
    public:
        FunScope(
            SharedBaseScope parentScope,
            SharedFunDecl decl,
            std::map<SharedWString, SharedVariable> locals,
            SharedVector<SharedIStatement> stmList
        );
        void check();
        SharedIValue invoke(std::map<SharedWString, SharedIValue> params);
        SharedClassScope getReturnType();
};