#include "DoWhileStatement.hpp"
#include "BoolValue.hpp"
#include "StmListScope.hpp"
#include "KeywordToken.hpp"
#include "IExpression.hpp"
#include "Type.hpp"
#include "FunScope.hpp"
#include "semantics/UnexpectedTypeException.hpp"

DoWhileStatement::DoWhileStatement(
    int lineNumber,
    SharedStmListScope runScope,
    SharedIExpression condition,
    SharedStmListScope doWhileScope
)
    : IStatement(lineNumber,runScope),
      condition(condition),
      doWhileScope(doWhileScope)
{}

void DoWhileStatement::check(){
    condition->check(runScope);
    
    if(condition->getReturnType()->getClassScope()!=Type::BOOL->getClassScope())
        throw UnexpectedTypeException(
            lineNumber,
            *Type::BOOL_NAME,
            *condition->getReturnType()->getName()
        );
    
    doWhileScope->check();
}

void DoWhileStatement::run(){
    auto stmList=doWhileScope->getStmList();
    auto funScope=BaseScope::getContainingFun(runScope);
    do{
        for(auto stm:*stmList){
            stm->run();
            if(funScope->getReturnValue())
                break;
        }
    }while(condition->evaluateAs<BoolValue>()->getValue());
}