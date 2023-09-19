#pragma once
#include "SharedPtrTypes.hpp"
#include "StmListScope.hpp"
#include <map>
#include <string>

class FunScope:public StmListScope{
    protected:
        SharedFunDecl decl;
        SharedIValue returnValue;
        // TODO: add params for shadowing
        // SharedMap<std::wstring, SharedVariable> params;
    public:
        FunScope(
            SharedBaseScope parentScope,
            SharedFunDecl decl
        );

        void accept(ASTVisitor *visitor) override;
        
        virtual SharedIValue invoke(SharedMap<std::wstring, SharedIValue> params);
        SharedType getReturnType();
        SharedFunDecl getDecl();
        void setReturnValue(SharedIValue returnValue);
        SharedIValue getReturnValue();
};