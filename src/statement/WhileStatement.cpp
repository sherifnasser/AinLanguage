#include "WhileStatement.hpp"
#include "BoolValue.hpp"
#include "StmListScope.hpp"
#include "IExpression.hpp"
#include "Type.hpp"
#include "LoopScope.hpp"
#include "UnexpectedTypeException.hpp"

WhileStatement::WhileStatement(
    int lineNumber,
    SharedStmListScope runScope,
    SharedIExpression condition,
    SharedLoopScope loopScope
)
    : IStatement(lineNumber,runScope),
      condition(condition),
      loopScope(loopScope)
{}

void WhileStatement::check(){
    condition->check(runScope);

    if(condition->getReturnType()->getClassScope()!=Type::BOOL->getClassScope())
        throw UnexpectedTypeException(
            lineNumber,
            *Type::BOOL_NAME,
            *condition->getReturnType()->getName()
        );
    
    loopScope->check();
}

void WhileStatement::run(){
    while(condition->evaluateAs<BoolValue>()->getValue()){

        loopScope->runStmList();

        if(loopScope->isContinue()){
            loopScope->resetContinue();
            continue;
        }

        if(loopScope->isBreak()){
            loopScope->resetBreak();
            break;
        }

        if(loopScope->isReturn())
            break;
        
    }
}