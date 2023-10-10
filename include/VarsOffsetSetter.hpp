#pragma once
#include "PackageScope.hpp"
#include "FileScope.hpp"
#include "ClassScope.hpp"
#include "FunScope.hpp"
#include "LoopScope.hpp"
#include "StmListScope.hpp"
#include "IfStatement.hpp"
#include "WhileStatement.hpp"
#include "DoWhileStatement.hpp"
class VarsOffsetSetter:public ASTVisitor{
    public:
        int stmListScopeOffset;
        struct Offset{
            Offset(int* reg, int value);
            Offset();
            int * reg=0;
            int value=0;
        };
        std::unordered_map<Variable*, Offset>* offsets;
        int*const BP;
        int*const BX;
        VarsOffsetSetter(
            std::unordered_map<Variable*, Offset>* offsets,
            int* BP,
            int* BX
        );
    private:
        void offsetStmListScope(StmListScope* scope);
        void visit(PackageScope* scope)override;
        void visit(FileScope* scope)override;
        void visit(ClassScope* scope)override;
        void visit(FunScope* scope)override;
        void visit(IfStatement* stm)override;
        void visit(WhileStatement* stm)override;
        void visit(DoWhileStatement* stm)override;
};