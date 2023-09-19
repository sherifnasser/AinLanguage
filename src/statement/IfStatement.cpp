#include "IfStatement.hpp"
#include "BoolValue.hpp"
#include "SharedPtrTypes.hpp"
#include "FunScope.hpp"
#include "IExpression.hpp"
#include "Type.hpp"
#include "UnexpectedTypeException.hpp"

IfStatement::IfStatement(
    int lineNumber,
    SharedStmListScope runScope,
    SharedIExpression ifCondition,
    SharedStmListScope ifScope,
    SharedStmListScope elseScope
)
    : IStatement(lineNumber,runScope),
      ifCondition(ifCondition),
      ifScope(ifScope),
      elseScope(elseScope),
      containingFunScope(BaseScope::getContainingFun(runScope))
{}

void IfStatement::run(){

    SharedStmList stmList;

    if(ifCondition->evaluateAs<BoolValue>()->getValue()){
        stmList=ifScope->getStmList();
    }
    else if(elseScope){
        stmList=elseScope->getStmList();
    }
    else return;
    
    for(auto stm:*stmList){
        stm->run();
        if(containingFunScope->getReturnValue())
            break;
    }
}

SharedIExpression IfStatement::getIfCondition()const{
    return ifCondition;
}

SharedStmListScope IfStatement::getIfScope()const{
    return ifScope;
}

SharedStmListScope IfStatement::getElseScope()const{
    return elseScope;
}

SharedFunScope IfStatement::getContainingFunScope()const{
    return containingFunScope;
}