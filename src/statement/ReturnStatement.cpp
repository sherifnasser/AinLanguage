#include "ReturnStatement.hpp"
#include "BaseScope.hpp"
#include "FunScope.hpp"
#include "SharedPtrTypes.hpp"
#include "Type.hpp"
#include "IExpression.hpp"
#include "UnexpectedTypeException.hpp"
#include "FunDecl.hpp"
#include "UnitExpression.hpp"
#include <memory>

ReturnStatement::ReturnStatement(
    int lineNumber,
    SharedStmListScope runScope,
    SharedIExpression ex
):IStatement(lineNumber,runScope),ex(ex){}

void ReturnStatement::check(){

    ex->check(runScope);

    auto exType=ex->getReturnType();

    auto funScope=BaseScope::getContainingFun(runScope);
    
    // Return statements in constructors should return Unit
    if(funScope->getDecl()->isConstructor()){
        if(exType->getClassScope()!=Type::UNIT->getClassScope())
            throw UnexpectedTypeException(
                lineNumber,
                *Type::UNIT_NAME,
                *exType->getName()
            );
    }
    else if(funScope->getReturnType()->getClassScope()!=exType->getClassScope())
        throw UnexpectedTypeException(
            lineNumber,
            *funScope->getReturnType()->getName(),
            *exType->getName()
        );
}

void ReturnStatement::run(){
    auto funScope=BaseScope::getContainingFun(runScope);
    funScope->setReturnValue(ex->evaluate());
}