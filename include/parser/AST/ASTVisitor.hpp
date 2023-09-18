#pragma once

class PackageScope;
class FileScope;
class ClassScope;
class ConstructorScope;
class FunScope;
class LoopScope;
class StmListScope;

class VarStm;
class IfStatement;
class AssignStatement;
class WhileStatement;
class DoWhileStatement;
class BreakStatement;
class ContinueStatement;
class ReturnStatement;
class ExpressionStatement;

class VarAccessExpression;
class FunInvokeExpression;
class NewObjectExpression;
class LiteralExpression;
class UnitExpression;

class LogicalExpression;
class IncDecExpression;
class EqualityExpression;
class CompareToExpression;

class NonStaticVarAccessExpression;
class NonStaticFunInvokeExpression;
class OperatorFunInvokeExpression;

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

        virtual ~ASTVisitor(){}

};