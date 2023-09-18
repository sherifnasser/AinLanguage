#pragma once
#include "ASTVisitor.hpp"

#include "PackageScope.hpp"
#include "FileScope.hpp"
#include "ClassScope.hpp"
#include "ConstructorScope.hpp"
#include "FunScope.hpp"
#include "LoopScope.hpp"
#include "StmListScope.hpp"
#include "VarStm.hpp"
#include "IfStatement.hpp"
#include "AssignStatement.hpp"
#include "WhileStatement.hpp"
#include "DoWhileStatement.hpp"
#include "BreakStatement.hpp"
#include "ContinueStatement.hpp"
#include "ReturnStatement.hpp"
#include "ExpressionStatement.hpp"
#include "VarAccessExpression.hpp"
#include "FunInvokeExpression.hpp"
#include "NewObjectExpression.hpp"
#include "LiteralExpression.hpp"
#include "UnitExpression.hpp"
#include "LogicalExpression.hpp"
#include "IncDecExpression.hpp"
#include "EqualityExpression.hpp"
#include "CompareToExpression.hpp"
#include "NonStaticVarAccessExpression.hpp"
#include "NonStaticFunInvokeExpression.hpp"
#include "OperatorFunInvokeExpression.hpp"
class SemanticsChecksVisitor:public ASTVisitor{
    public:
        void visit(PackageScope* scope)override;
        void visit(FileScope* scope)override;
        void visit(ClassScope* scope)override;
        void visit(ConstructorScope* scope)override;
        void visit(FunScope* scope)override;
        void visit(LoopScope* scope)override;
        void visit(StmListScope* scope)override;

        void visit(VarStm* stm)override;
        void visit(AssignStatement* stm)override;
        void visit(IfStatement* stm)override;
        void visit(WhileStatement* stm)override;
        void visit(DoWhileStatement* stm)override;
        void visit(BreakStatement* stm)override;
        void visit(ContinueStatement* stm)override;
        void visit(ReturnStatement* stm)override;
        void visit(ExpressionStatement* stm)override;

        void visit(VarAccessExpression* ex)override;
        void visit(FunInvokeExpression* ex)override;
        void visit(NewObjectExpression* ex)override;
        void visit(LiteralExpression* ex)override;
        void visit(UnitExpression* ex)override;

        void visit(LogicalExpression* ex)override;
        void visit(IncDecExpression* ex)override;
        void visit(EqualityExpression* ex)override;
        void visit(CompareToExpression* ex)override;
        
        void visit(NonStaticVarAccessExpression* ex)override;
        void visit(NonStaticFunInvokeExpression* ex)override;
        void visit(OperatorFunInvokeExpression* ex)override;
};