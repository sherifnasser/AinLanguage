#pragma once
#include "StmListScope.hpp"
class LoopScope:public StmListScope{
    public:
        LoopScope(SharedBaseScope parentScope);
        void accept(ASTVisitor *visitor) override;
};