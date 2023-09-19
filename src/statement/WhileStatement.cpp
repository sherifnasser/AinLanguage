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

SharedIExpression WhileStatement::getCondition()const{
    return condition;
}

SharedLoopScope WhileStatement::getLoopScope()const{
    return loopScope;
}