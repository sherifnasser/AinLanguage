#include "ReturnStatement.hpp"
#include "BaseScope.hpp"
#include "FunScope.hpp"
#include "SharedPtrTypes.hpp"
#include "Type.hpp"
#include "IExpression.hpp"
#include "semantics/UnexpectedTypeException.hpp"


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
    else exType=Type::UNIT;

    auto funScope=BaseScope::getContainingFun(runScope);

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