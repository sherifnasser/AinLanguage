#include "DoWhileStatement.hpp"
#include "BoolValue.hpp"
#include "SharedPtrTypes.hpp"
#include "IExpression.hpp"
#include "LoopScope.hpp"

void DoWhileStatement::run(){
    
    do{
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
        
    }while(condition->evaluateAs<BoolValue>()->getValue());
}