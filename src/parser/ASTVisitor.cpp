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

void PackageScope::accept(ASTVisitor* visitor){
    visitor->visit(this);
}

void FileScope::accept(ASTVisitor* visitor){
    visitor->visit(this);
}

void ClassScope::accept(ASTVisitor* visitor){
    visitor->visit(this);
}

void ConstructorScope::accept(ASTVisitor* visitor){
    visitor->visit(this);
}

void FunScope::accept(ASTVisitor* visitor){
    visitor->visit(this);
}

void LoopScope::accept(ASTVisitor* visitor){
    visitor->visit(this);
}

void StmListScope::accept(ASTVisitor* visitor){
    visitor->visit(this);
}

void VarStm::accept(ASTVisitor* visitor){
    visitor->visit(this);
}

void IfStatement::accept(ASTVisitor* visitor){
    visitor->visit(this);
}

void AssignStatement::accept(ASTVisitor* visitor){
    visitor->visit(this);
}

void WhileStatement::accept(ASTVisitor* visitor){
    visitor->visit(this);
}

void DoWhileStatement::accept(ASTVisitor* visitor){
    visitor->visit(this);
}

void BreakStatement::accept(ASTVisitor* visitor){
    visitor->visit(this);
}

void ContinueStatement::accept(ASTVisitor* visitor){
    visitor->visit(this);
}

void ReturnStatement::accept(ASTVisitor* visitor){
    visitor->visit(this);
}

void ExpressionStatement::accept(ASTVisitor* visitor){
    visitor->visit(this);
}

void VarAccessExpression::accept(ASTVisitor* visitor){
    visitor->visit(this);
}

void FunInvokeExpression::accept(ASTVisitor* visitor){
    visitor->visit(this);
}

void NewObjectExpression::accept(ASTVisitor* visitor){
    visitor->visit(this);
}

void LiteralExpression::accept(ASTVisitor* visitor){
    visitor->visit(this);
}

void UnitExpression::accept(ASTVisitor* visitor){
    visitor->visit(this);
}

void LogicalExpression::accept(ASTVisitor* visitor){
    visitor->visit(this);
}

void IncDecExpression::accept(ASTVisitor* visitor){
    visitor->visit(this);
}

void EqualityExpression::accept(ASTVisitor* visitor){
    visitor->visit(this);
}

void CompareToExpression::accept(ASTVisitor* visitor){
    visitor->visit(this);
}

void NonStaticVarAccessExpression::accept(ASTVisitor* visitor){
    visitor->visit(this);
}

void NonStaticFunInvokeExpression::accept(ASTVisitor* visitor){
    visitor->visit(this);
}

void OperatorFunInvokeExpression::accept(ASTVisitor* visitor){
    visitor->visit(this);
}
