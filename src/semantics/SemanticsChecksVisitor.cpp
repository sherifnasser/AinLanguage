#include "SemanticsChecksVisitor.hpp"
#include "BaseScope.hpp"
#include "FunDecl.hpp"
#include "InvalidOperatorFunDeclarationException.hpp"
#include "OperatorFunctions.hpp"
#include "TypeMismatchException.hpp"
#include "UnexpectedTypeException.hpp"
#include "Variable.hpp"

void SemanticsChecksVisitor::visit(PackageScope* scope){
    for(auto fileIt:scope->getFiles()){
        fileIt.second->accept(this);
    }

    for(auto packageIt:scope->getPackages()){
        packageIt.second->accept(this);
    }

}

void SemanticsChecksVisitor::visit(FileScope* scope){

    scope->getGlobalVarsInitStmList()->accept(this);

    for(auto classIterator:*scope->getPrivateClasses()){
	    classIterator.second->accept(this);
    }
    for(auto classIterator:*scope->getPublicClasses()){
	    classIterator.second->accept(this);
    }
    for(auto funIterator:*scope->getPrivateFunctions()){
        funIterator.second->accept(this);
    }
    for(auto funIterator:*scope->getPublicFunctions()){
        funIterator.second->accept(this);
    }
}

void SemanticsChecksVisitor::visit(ClassScope* scope){

    scope->getVarsInitStmList()->accept(this);

    for(auto constructorIterator:*scope->getPrivateConstructors()){
        constructorIterator.second->accept(this);
    }
    for(auto constructorIterator:*scope->getPublicConstructors()){
        constructorIterator.second->accept(this);
    }
    for(auto funIterator:*scope->getPrivateFunctions()){
        funIterator.second->accept(this);
    }
    for(auto funIterator:*scope->getPublicFunctions()){
        funIterator.second->accept(this);
    }
}

void SemanticsChecksVisitor::visit(ConstructorScope* scope){
    doStmListScopeChecks(scope);
}

void SemanticsChecksVisitor::visit(FunScope* scope){
    if(*scope->getDecl()->isOperator)
        doOperatorFunChecks(scope);

    doStmListScopeChecks(scope);
}

void SemanticsChecksVisitor::visit(LoopScope* scope){ 
    doStmListScopeChecks(scope);
}

void SemanticsChecksVisitor::visit(StmListScope* scope){
    doStmListScopeChecks(scope);
}

void SemanticsChecksVisitor::visit(VarStm* stm){

    auto var=stm->getVar();

    auto ex=stm->getEx();

    ex->accept(this);

    auto exType=ex->getReturnType();

    if(var->hasImplicitType()){
        var->setType(exType);
        return;
    }

    if(*var->getType()==*exType)
        return;
    
    // TODO: message
    throw TypeMismatchException(
        L"متغير "+*var->getName()+L": "+*var->getType()->getName(),
        L"تعبير: "+*ex->getReturnType()->getName());

}

void SemanticsChecksVisitor::visit(AssignStatement* stm){

    auto ex=stm->getEx();

    auto newValEx=stm->getNewValEx();

    ex->accept(this);
    newValEx->accept(this);

    auto t1=ex->getReturnType();

    auto t2=newValEx->getReturnType();

    if(t1->getClassScope()!=t2->getClassScope())
        throw UnexpectedTypeException(
            stm->getLineNumber(),
            *t1->getName(),
            *t2->getName()
        );
}

void SemanticsChecksVisitor::visit(IfStatement* stm){

    auto ifCondition=stm->getIfCondition();

    ifCondition->accept(this);

    if(ifCondition->getReturnType()->getClassScope()!=Type::BOOL->getClassScope())
        throw UnexpectedTypeException(
            stm->getLineNumber(),
            *Type::BOOL_NAME,
            *ifCondition->getReturnType()->getName()
        );
    
    stm->getIfScope()->accept(this);

    if(auto elseScope=stm->getElseScope())
        elseScope->accept(this);
}

void SemanticsChecksVisitor::visit(WhileStatement* stm){
    doWhileStmChecks(stm);    
}

void SemanticsChecksVisitor::visit(DoWhileStatement* stm){
    doWhileStmChecks(stm);
}

void SemanticsChecksVisitor::visit(ReturnStatement* stm){
    auto ex=stm->getEx();

    ex->accept(this);

    auto exType=ex->getReturnType();

    auto funScope=BaseScope::getContainingFun(stm->getRunScope());
    
    // Return statements in constructors should return Unit
    if(funScope->getDecl()->isConstructor()){
        if(exType->getClassScope()!=Type::UNIT->getClassScope())
            throw UnexpectedTypeException(
                stm->getLineNumber(),
                *Type::UNIT_NAME,
                *exType->getName()
            );
    }
    else if(funScope->getReturnType()->getClassScope()!=exType->getClassScope())
        throw UnexpectedTypeException(
            stm->getLineNumber(),
            *funScope->getReturnType()->getName(),
            *exType->getName()
        );
}

void SemanticsChecksVisitor::visit(ExpressionStatement* stm){
    stm->getEx()->accept(this);
}

void SemanticsChecksVisitor::visit(VarAccessExpression* ex){
    
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

void SemanticsChecksVisitor::visit(NonStaticVarAccessExpression* ex) {
    
}

void SemanticsChecksVisitor::visit(NonStaticFunInvokeExpression* ex) {
    
}

void SemanticsChecksVisitor::visit(OperatorFunInvokeExpression* ex) {
    
}

void SemanticsChecksVisitor::doWhileStmChecks(WhileStatement* stm){
    auto condition=stm->getCondition();

    condition->accept(this);

    if(condition->getReturnType()->getClassScope()!=Type::BOOL->getClassScope())
        throw UnexpectedTypeException(
            stm->getLineNumber(),
            *Type::BOOL_NAME,
            *condition->getReturnType()->getName()
        );
    
    stm->getLoopScope()->accept(this);
}

void SemanticsChecksVisitor::doStmListScopeChecks(StmListScope* scope){
    for(auto stm:*scope->getStmList()){
        stm->accept(this);
    }
}

void SemanticsChecksVisitor::doOperatorFunChecks(FunScope* scope){
    checkOperatorFunParamsSize(scope);
    checkOperatorFunReturnType(scope);
}

void SemanticsChecksVisitor::checkOperatorFunParamsSize(FunScope* scope){

    auto opName=scope->getName();
    auto paramsSize=scope->getDecl()->params->size();

    auto isBinOp=
        opName==OperatorFunctions::PLUS_NAME
        ||
        opName==OperatorFunctions::MINUS_NAME
        ||
        opName==OperatorFunctions::TIMES_NAME
        ||
        opName==OperatorFunctions::DIV_NAME
        ||
        opName==OperatorFunctions::MOD_NAME
        ||
        opName==OperatorFunctions::POW_NAME
    ;

    if(isBinOp&&paramsSize!=1)
        throw InvalidOperatorFunDeclarationException(L"عدد المعاملات غير صالح لدالة "+opName);

    auto isUnaryOp=
        opName==OperatorFunctions::UNARY_PLUS_NAME
        ||
        opName==OperatorFunctions::UNARY_MINUS_NAME
        ||
        opName==OperatorFunctions::LOGICAL_NOT_NAME
        ||
        opName==OperatorFunctions::INC_NAME
        ||
        opName==OperatorFunctions::DEC_NAME
    ;

    if(isUnaryOp&&paramsSize!=0)
        throw InvalidOperatorFunDeclarationException(L"عدد المعاملات غير صالح لدالة "+opName);

}

void SemanticsChecksVisitor::checkOperatorFunReturnType(FunScope* scope){
    auto opName=scope->getName();

    auto returnType=scope->getReturnType();

    if(opName==OperatorFunctions::COMPARE_TO_NAME&&*returnType->getName()!=*Type::INT_NAME)
        throw InvalidOperatorFunDeclarationException(L"دالة قارن_مع يجب أن ترجع قيمة من نوع صحيح.");

    if(opName==OperatorFunctions::EQUALS_NAME&&*returnType->getName()!=*Type::BOOL_NAME)
        throw InvalidOperatorFunDeclarationException(L"دالة يساوي يجب أن ترجع قيمة من نوع منطقي.");
    
    auto parentClass=BaseScope::getContainingClass(scope->getParentScope());
    if(
        (opName==OperatorFunctions::INC_NAME||opName==OperatorFunctions::DEC_NAME)
        &&
        returnType->getClassScope()!=parentClass
    )
        throw InvalidOperatorFunDeclarationException(
            L"دالة "+opName+
            L" يجب أن ترجع قيمة من نفس نوع "+parentClass->getName()
        );
    
}
