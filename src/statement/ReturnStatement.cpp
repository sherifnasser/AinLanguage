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
    SharedType exType;
    if(ex){
        ex->check(runScope);
        exType=ex->getReturnType();
    }
    else{
        ex=std::make_shared<UnitExpression>(lineNumber);
        exType=Type::UNIT;
    }

    auto funScope=BaseScope::getContainingFun(runScope);
    
    // Return statements in constructors should return Unit
    if(funScope->getDecl()->isConstructor()&&exType->getClassScope()!=Type::UNIT->getClassScope())
        throw UnexpectedTypeException(
            lineNumber,
            *Type::UNIT_NAME,
            *exType->getName()
        );
    
    if(funScope->getReturnType()->getClassScope()!=exType->getClassScope())
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