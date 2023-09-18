#pragma once

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

class ASTVisitor{
    public:
        virtual void visit(PackageScope* scope)=0;
        virtual void visit(FileScope* scope)=0;
        virtual void visit(ClassScope* scope)=0;
        virtual void visit(ConstructorScope* scope)=0;
        virtual void visit(FunScope* scope)=0;
        virtual void visit(LoopScope* scope)=0;
        virtual void visit(StmListScope* scope)=0;

        virtual void visit(VarStm* stm)=0;
        virtual void visit(AssignStatement* stm)=0;
        virtual void visit(IfStatement* stm)=0;
        virtual void visit(WhileStatement* stm)=0;
        virtual void visit(DoWhileStatement* stm)=0;
        virtual void visit(BreakStatement* stm)=0;
        virtual void visit(ContinueStatement* stm)=0;
        virtual void visit(ReturnStatement* stm)=0;
        virtual void visit(ExpressionStatement* stm)=0;

        virtual void visit(VarAccessExpression* ex)=0;
        virtual void visit(FunInvokeExpression* ex)=0;
        virtual void visit(NewObjectExpression* ex)=0;
        virtual void visit(LiteralExpression* ex)=0;
        virtual void visit(UnitExpression* ex)=0;

        virtual void visit(LogicalExpression* ex)=0;
        virtual void visit(IncDecExpression* ex)=0;
        virtual void visit(EqualityExpression* ex)=0;
        virtual void visit(CompareToExpression* ex)=0;
        
        virtual void visit(NonStaticVarAccessExpression* ex)=0;
        virtual void visit(NonStaticFunInvokeExpression* ex)=0;
        virtual void visit(OperatorFunInvokeExpression* ex)=0;


};