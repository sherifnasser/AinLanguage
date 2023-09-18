#pragma once
#include "FunScope.hpp"
#include "SharedPtrTypes.hpp"
class ConstructorScope:public FunScope{
    public:
        ConstructorScope(SharedFunDecl decl);

        void accept(ASTVisitor *visitor) override;
        
        SharedIValue invoke(SharedMap<std::wstring, SharedIValue> params) override;
};