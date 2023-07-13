#include "AssignStatement.hpp"
#include "StmListScope.hpp"
#include "Type.hpp"
#include "semantics/UnexpectedTypeException.hpp"

AssignStatement::AssignStatement(
    int lineNumber,
    SharedStmListScope runScope,
    std::shared_ptr<AssignExpression> ex,
    SharedIExpression newValEx
)
:IStatement(lineNumber,runScope),ex(ex),newValEx(newValEx){}

void AssignStatement::check(){
    ex->check(runScope);
    newValEx->check(runScope);
    auto t1=ex->getReturnType();
    auto t2=newValEx->getReturnType();
    if(t1->getClassScope()!=t2->getClassScope())
        throw UnexpectedTypeException(
            lineNumber,
            *t1->getName(),
            *t2->getName()
        );
}

void AssignStatement::run(){
    ex->assign(
        newValEx->evaluate()
    );
}