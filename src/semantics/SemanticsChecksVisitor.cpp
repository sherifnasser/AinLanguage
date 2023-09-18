#include "SemanticsChecksVisitor.hpp"

void SemanticsChecksVisitor::visit(PackageScope* scope){
    std::wcout<<L"Package: "<<scope->getName()<<std::endl;
    
    for(auto fileIt:scope->getFiles()){
        fileIt.second->accept(this);
    }

    for(auto packageIt:scope->getPackages()){
        packageIt.second->accept(this);
    }

}

void SemanticsChecksVisitor::visit(FileScope* scope) {
    std::wcout<<L"File: "<<scope->getName()<<std::endl;
}

void SemanticsChecksVisitor::visit(ClassScope* scope) {
    
}

void SemanticsChecksVisitor::visit(ConstructorScope* scope) {
    
}

void SemanticsChecksVisitor::visit(FunScope* scope) {
    
}

void SemanticsChecksVisitor::visit(LoopScope* scope) {
    
}

void SemanticsChecksVisitor::visit(StmListScope* scope) {
    
}

void SemanticsChecksVisitor::visit(VarStm* stm) {
    
}

void SemanticsChecksVisitor::visit(AssignStatement* stm) {
    
}

void SemanticsChecksVisitor::visit(IfStatement* stm) {
    
}

void SemanticsChecksVisitor::visit(WhileStatement* stm) {
    
}

void SemanticsChecksVisitor::visit(DoWhileStatement* stm) {
    
}

void SemanticsChecksVisitor::visit(BreakStatement* stm) {
    
}

void SemanticsChecksVisitor::visit(ContinueStatement* stm) {
    
}

void SemanticsChecksVisitor::visit(ReturnStatement* stm) {
    
}

void SemanticsChecksVisitor::visit(ExpressionStatement* stm) {
    
}

void SemanticsChecksVisitor::visit(VarAccessExpression* ex) {
    
}

void SemanticsChecksVisitor::visit(FunInvokeExpression* ex) {
    
}

void SemanticsChecksVisitor::visit(NewObjectExpression* ex) {
    
}

void SemanticsChecksVisitor::visit(LiteralExpression* ex) {
    
}

void SemanticsChecksVisitor::visit(UnitExpression* ex) {
    
}

void SemanticsChecksVisitor::visit(LogicalExpression* ex) {
    
}

void SemanticsChecksVisitor::visit(IncDecExpression* ex) {
    
}

void SemanticsChecksVisitor::visit(EqualityExpression* ex) {
    
}

void SemanticsChecksVisitor::visit(CompareToExpression* ex) {
    
}

void SemanticsChecksVisitor::visit(NonStaticVarAccessExpression* ex) {
    
}

void SemanticsChecksVisitor::visit(NonStaticFunInvokeExpression* ex) {
    
}

void SemanticsChecksVisitor::visit(OperatorFunInvokeExpression* ex) {
    
}
